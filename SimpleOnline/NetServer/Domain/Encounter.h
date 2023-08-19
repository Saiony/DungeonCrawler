#pragma once
#include <memory>
#include <vector>
#include "Player.h"
#include "Enemies/base_enemy.h"

namespace dungeon_server::domain
{
    class base_enemy;
    
    class encounter
    {
    public:
        std::vector<std::shared_ptr<base_enemy>> enemies;
        std::vector<std::shared_ptr<player>> players;
        std::vector<std::shared_ptr<base_creature>> creatures;
        std::shared_ptr<base_creature> active_creature;
        bool game_over = false;
        bool players_won = false;
        
        encounter(std::vector<std::shared_ptr<base_enemy>> enemies, std::vector<std::shared_ptr<player>> players, std::shared_ptr<base_creature> active_creature);
        void go_to_next_turn();
        void set_game_over(bool players_won_encounter);
    };
}
