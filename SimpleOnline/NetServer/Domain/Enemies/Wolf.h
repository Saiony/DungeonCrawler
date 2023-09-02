#pragma once
#include "base_enemy.h"

namespace dungeon_server::domain::enemy
{
    class wolf final : public base_enemy
    {
    public:
        wolf(const std::string& new_name, uint16_t new_health, uint16_t new_damage, uint16_t new_ability_power);
        void on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) override;
    };
}
