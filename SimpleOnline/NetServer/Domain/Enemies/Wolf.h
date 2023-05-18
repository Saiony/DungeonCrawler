#pragma once
#include "BaseEnemy.h"

namespace dungeon_server::domain::enemy
{
    class wolf : public base_enemy
    {
    public:
        wolf(const std::string& name, uint16_t health, uint16_t damage);
        void execute_turn() override;
    };
}
