#pragma once
#include <memory>
#include <vector>
#include "Player.h"
#include "Enemies/BaseEnemy.h"

namespace dungeon_server::domain
{
    class encounter
    {
    public:
        std::vector<enemy::base_enemy> enemies;
        std::vector<player> players;
        std::vector<std::shared_ptr<base_creature>> creatures;
        base_creature active_creature;
        
        encounter(std::vector<enemy::base_enemy> enemies, std::vector<player> players, base_creature active_creature);
    };
}
