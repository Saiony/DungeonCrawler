#pragma once
#include "BaseEnemy.h"

namespace dungeon_server::domain::enemy
{
    class wolf final : public base_enemy
    {
    public:
        wolf(const std::string& new_name, const uint16_t new_health, const uint16_t new_damage, const uint16_t new_ability_power);
        std::string execute_turn(const std::shared_ptr<encounter>& encounter_ptr) override;
    };
}
