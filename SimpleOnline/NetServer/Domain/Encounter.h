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
        std::vector<std::shared_ptr<base_enemy>> enemies;
        std::vector<std::shared_ptr<player>> players;
        std::vector<std::shared_ptr<base_creature>> creatures;
        std::shared_ptr<base_creature> active_creature;
        
        encounter(std::vector<std::shared_ptr<base_enemy>> enemies, std::vector<std::shared_ptr<player>> players, std::shared_ptr<base_creature> active_creature);
        void go_to_next_turn();
    };
}
