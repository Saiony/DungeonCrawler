#pragma once
#include <memory>
#include <vector>
#include "enemy.h"
#include "Player.h"

namespace dungeon_client::domain
{    
    class encounter
    {
    public:
        std::vector<enemy> enemies;
        std::vector<player> players;
        std::unique_ptr<base_creature> active_creature_ptr;
        
        encounter(std::vector<enemy> enemies, std::vector<player> players, std::string active_player_id);
        bool check_active_player(const player& player) const;
    };
}
