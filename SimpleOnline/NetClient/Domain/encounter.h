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
        std::string log;
        
        encounter(std::vector<enemy> enemies, std::vector<player> players, const std::string& active_creature_id, const std::string& log);
        bool check_active_player(const player& player) const;
    };
}
