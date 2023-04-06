#pragma once
#include <vector>
#include "Enemies/BaseEnemy.h"


namespace dungeon_server::domain::encounter
{
    class encounter
    {
    private:
        std::vector<enemy::base_enemy> enemies_;
    public:
        encounter(std::vector<enemy::base_enemy> enemies);
    };
}
