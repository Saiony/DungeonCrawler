#include "game_room.h"
#include "net_message.h"
#include "NetServer/Domain/Enemies/Wolf.h"
#include "NetServer/Domain/Message/match_start_response.h"
#include "states/base_game_room_state.h"
#include "states/game_room_combat_state.h"

dungeon_server::game_room::game_room::game_room(std::vector<std::shared_ptr<domain::player>> players,
                                                const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function)
                                                : players_(std::move(players)), encounter_(generate_encounter()),
                                                state_ptr_(std::make_unique<game_room_combat_state>(encounter_))
{
    send_inner_message = send_message_function;
}

std::shared_ptr<dungeon_server::domain::encounter> dungeon_server::game_room::game_room::generate_encounter() const
{
    const domain::enemy::wolf wolf("wolf", 10, 5, 1);
    std::vector<std::shared_ptr<domain::base_enemy>> enemies;
    enemies.push_back(std::make_shared<domain::enemy::wolf>(wolf));
    auto encounter = std::make_shared<domain::encounter>(enemies, players_, players_[0]);
    
    return encounter;
}

void dungeon_server::game_room::game_room::player_match_start_request(std::shared_ptr<domain::player>& player)
{
    const auto msg = std::make_shared<domain::message::match_start_response>(player, encounter_);
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