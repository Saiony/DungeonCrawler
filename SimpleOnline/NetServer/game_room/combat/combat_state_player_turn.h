#pragma once
#include "NetServer/Domain/Player.h"
#include "NetServer/Domain/Actions/base_action.h"
#include "NetServer/game_room/states/base_state.h"
#include "NetServer/game_room/states/game_room_combat_state.h"

namespace dungeon_server::game_room::combat
{
    template<typename T>
    class combat_state_player_turn final : public base_state<T>
    {    
    private:
        domain::player active_player_;

    public:
        explicit combat_state_player_turn(domain::player player): active_player_(player)
        {
        }

        void update()
        {
        }

        void handle_player_action(domain::player player, domain::action::base_action action)
        {
        }
    };
}
