#include "game_room.h"
#include "net_message.h"
#include "NetServer/Domain/Message/match_start_response.h"
#include "states/base_game_room_state.h"
#include "states/game_room_combat_state.h"

dungeon_server::game_room::game_room::game_room(std::vector<std::shared_ptr<domain::player>> players,
                                                const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function)
                                                : players_(std::move(players)),
                                                encounter_manager_(std::make_shared<domain::encounter_manager>(players_)),
                                                state_ptr_(std::make_unique<game_room_combat_state>(encounter_manager_))
{
    send_inner_message = send_message_function;
}

void dungeon_server::game_room::game_room::player_match_start_request(std::shared_ptr<domain::player>& player) const
{
    const auto msg = std::make_shared<domain::message::match_start_response>(player, encounter_manager_->current_encounter);
    send_inner_message(msg);
}

void dungeon_server::game_room::game_room::set_state(const base_game_room_state& state)
{
    state_ptr_->on_end();    
    state_ptr_ = std::make_unique<base_game_room_state>(state);
    state_ptr_->on_start();
}

void dungeon_server::game_room::game_room::handle_player_input(const std::shared_ptr<domain::action::base_action>& action_ptr) const
{
    state_ptr_->handle_input(send_inner_message, action_ptr);
}

void dungeon_server::game_room::game_room::update() const
{
    state_ptr_->update(send_inner_message);
}