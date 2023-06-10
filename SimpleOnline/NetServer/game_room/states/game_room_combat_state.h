#pragma once
#include "base_state.h"
#include "NetServer/Domain/Encounter.h"
#include "NetServer/Domain/Player.h"

namespace dungeon_server::game_room
{
    template<typename T>
    class game_room_combat_state final : public base_state<T>
    {
    private:
        domain::player active_player_;
        base_state<T> state_;

    public:
        explicit game_room_combat_state(const domain::encounter& encounter): active_player_(encounter.players[0])
        {
        }

        void handle_input(const T& game_room, domain::action::base_action action) override
        {
        }

        void update(const T& game_room) override
        {
        }

        void on_start(const T& game_room) override
        {
        }

        void on_end(const T& game_room) override
        {
        }
    };
}
