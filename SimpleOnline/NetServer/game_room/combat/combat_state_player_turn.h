#pragma once
#include "base_combat_state.h"
#include "NetServer/Domain/Player.h"
#include "NetServer/Domain/Actions/base_action.h"

namespace dungeon_server::game_room::combat
{
    class combat_state_player_turn final : public base_combat_state
    {    
    private:
        domain::player active_player_;

    public:
        explicit combat_state_player_turn(const domain::player& active_player): active_player_(active_player)
        {
        }

        void handle_player_action(const domain::player& player, const domain::action::base_action& action) override
        {
            
        }

        void update() override
        {
        }
    };
}
