#include "game_room.h"

#include "net_message.h"
#include "NetServer/Domain/Enemies/Wolf.h"
#include "NetServer/Domain/Message/match_start_response.h"
#include "states/game_room_combat_state.h"

dungeon_server::game_room::game_room::game_room(std::vector<domain::player> players,
            const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function)
        :
            state_ptr_(std::make_unique<game_room_combat_state<game_room>>(encounter_)),
            players_(std::move(players)),
            encounter_(get_encounter())
{
    send_inner_message_ = send_message_function;
    
    //historia -> combate

    //LOOP
    //player 0 habilitado para jogar
    //player 0 escolhe uma habilidade da lista de habilidades
    //passa a vez

    //player 1 habilitado para jogar
    //player 1 escolhe uma habilidade da lista de habilidades
    //passa a vez

    //inimigo 1 habilitado para jogar
    //inimigo 1 escolhe uma habilidade da lista de habilidades
    //passa a vez
    //FIM DO LOOP
}

dungeon_server::domain::encounter dungeon_server::game_room::game_room::get_encounter() const
{
    const domain::enemy::wolf wolf("wolf", 10, 15);
    const std::vector enemies = { static_cast<domain::enemy::base_enemy>(wolf) };    
    domain::encounter encounter(enemies, players_);
    
    return encounter;
}

void dungeon_server::game_room::game_room::player_match_start_request(const domain::player& player) const
{
    auto encounter = get_encounter();
    const auto x = std::make_shared<domain::message::match_start_response>(player, encounter);
    send_inner_message_(x);
}

void dungeon_server::game_room::game_room::set_state(const base_state<game_room>& state)
{
    state_ptr_->on_end(*this);    
    state_ptr_ = std::make_unique<base_state<game_room>>(state);
    state_ptr_->on_start(*this);
}

void dungeon_server::game_room::game_room::handle_player_input(domain::action::base_action action) const
{
    state_ptr_->handle_input(*this, action);
}

void dungeon_server::game_room::game_room::update() const
{
    state_ptr_->update(*this);
}