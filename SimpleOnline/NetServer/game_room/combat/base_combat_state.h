#pragma once
#include "NetServer/Domain/Player.h"
#include "NetServer/Domain/Actions/base_action.h"

namespace dungeon_server::game_room::combat
{
    class base_combat_state
    {
    public:
        virtual void update()
        {
        }

        virtual void handle_player_action(const domain::player& player, const domain::action::base_action& action)
        {
        }
    };
}
