#include "game_room.h"
#include "NetServer/Domain/Message/match_start_response.h"
#include "states/base_game_room_state.h"
#include "states/game_room_bonfire_state.h"
#include "states/game_room_combat_state.h"
#include "states/game_room_game_over_lose_state.h"
#include "states/game_room_game_over_win_state.h"
#include "states/game_room_story_state.h"

dungeon_server::game_room::game_room::game_room(std::vector<std::shared_ptr<domain::player>> players,
                                                const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function)
    : players_(std::move(players)),
      encounter_manager_(std::make_shared<domain::encounter_manager>(players_)),
      state_ptr(std::make_shared<game_room_story_state>(level_, players_, send_inner_message,
                                                        [this] { on_state_ended(); }))
{
    send_inner_message = send_message_function;
}

void dungeon_server::game_room::game_room::go_to_next_state()
{
    if (game_over_)
    {
        const auto new_state = std::make_shared<game_room_game_over_lose_state>(send_inner_message);
        set_state(new_state);
    }
    else if (level_ > max_level_)
    {
        const auto new_state = std::make_shared<game_room_game_over_win_state>(send_inner_message);
        set_state(new_state);
    }
    else if (std::dynamic_pointer_cast<game_room_story_state>(state_ptr))
    {
        const auto new_state = std::make_shared<game_room_combat_state>(encounter_manager_, level_, send_inner_message,
                                                                        [this] { on_state_ended(); },
                                                                        [this] { on_players_lost(); });
        set_state(new_state);
    }
    else if (auto combat_state = std::dynamic_pointer_cast<game_room_combat_state>(state_ptr))
    {
        const auto new_state = std::make_shared<game_room_bonfire_state>(players_, send_inner_message,
                                                                         [this] { on_state_ended(); });
        set_state(new_state);
    }
    else if (auto bonfire_state = std::dynamic_pointer_cast<game_room_bonfire_state>(state_ptr))
    {
        level_++;
        const auto new_state = std::make_shared<game_room_story_state>(level_, players_, send_inner_message,
                                                                       [this] { on_state_ended(); });
        set_state(new_state);
    }
}

void dungeon_server::game_room::game_room::set_state(const std::shared_ptr<base_game_room_state>& state)
{
    state_ptr->on_end();
    state_ptr = state;
}

void dungeon_server::game_room::game_room::player_match_start_request(std::shared_ptr<domain::player>& player) const
{
    if (!std::dynamic_pointer_cast<game_room_combat_state>(state_ptr))
        throw std::exception("Invalid message for current state");

    state_ptr->on_start();
    const auto msg = std::make_shared<domain::message::match_start_response>(player, encounter_manager_->current_encounter);
    send_inner_message(msg);
}

void dungeon_server::game_room::game_room::handle_player_input(const std::shared_ptr<domain::action::base_action>& action_ptr) const
{
    state_ptr->handle_input(action_ptr);
}

void dungeon_server::game_room::game_room::request_story(const std::shared_ptr<domain::player>& player) const
{
    const auto story_state = std::dynamic_pointer_cast<game_room_story_state>(state_ptr);

    if (!story_state)
        throw std::exception("Invalid message for current state");

    story_state->request_story(player);
}

void dungeon_server::game_room::game_room::set_story_read(const std::shared_ptr<domain::player>& player) const
{
    const auto story_state = std::dynamic_pointer_cast<game_room_story_state>(state_ptr);

    if (!story_state)
        throw std::exception("Invalid message for current state");

    story_state->confirm_story_read(player);
}

void dungeon_server::game_room::game_room::request_bonfire_story_teller(const std::shared_ptr<domain::player>& player) const
{
    const auto bonfire_state = std::dynamic_pointer_cast<game_room_bonfire_state>(state_ptr);

    if (!bonfire_state)
        throw std::exception("Invalid message for current state");

    bonfire_state->request_story_teller(player);
}

void dungeon_server::game_room::game_room::update() const
{
    state_ptr->update();
}

void dungeon_server::game_room::game_room::on_state_ended()
{
    go_to_next_state();
}

void dungeon_server::game_room::game_room::on_players_lost()
{
    game_over_ = true;
}
