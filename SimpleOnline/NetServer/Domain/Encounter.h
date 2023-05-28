#pragma once
#include <vector>
#include "Enemies/BaseEnemy.h"


namespace dungeon_server::domain::encounter
{
    class encounter
    {
    public:
        std::vector<enemy::base_enemy> enemies;
        explicit encounter(std::vector<enemy::base_enemy> enemies);
    };
}
