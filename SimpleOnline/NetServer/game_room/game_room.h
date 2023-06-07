#pragma once
#include <memory>

#include "net_message.h"
#include "NetServer/Domain/Actions/base_action.h"
#include "NetServer/Domain/Message/emitter_message.h"
#include "states/game_room_combat_state.h"

namespace dungeon_server::game_room
{
    class game_room
    {
    private:
        std::unique_ptr<base_state<game_room>> state_ptr_;
        std::vector<domain::player> players_;
        game_room_combat_state<game_room> encounter_;

        domain::encounter::encounter get_encounter() const;
        std::function<void(std::shared_ptr<emitter_message>)> send_message_;
    public:
        explicit game_room(std::vector<domain::player> players, const std::function<void(std::shared_ptr<emitter_message>)>& send_message_function);
        void player_match_start_request(const domain::player& player) const;
        void set_state(const base_state<game_room>& state);
        void handle_player_input(domain::action::base_action action) const;
        void update() const;
    };
}
