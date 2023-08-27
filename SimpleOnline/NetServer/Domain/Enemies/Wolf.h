#pragma once
#include "base_enemy.h"

namespace dungeon_server::domain::enemy
{
    class wolf final : public base_enemy
    {
    public:
        wolf(const std::string& new_name, const uint16_t new_health, const uint16_t new_damage, const uint16_t new_ability_power);
        void on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) override;
    };
}
