#pragma once
#include "base_enemy.h"

namespace dungeon_server::domain::enemy
{
    class goblin_warrior final : public base_enemy
    {
    protected:
        void on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) override;
    public:
        goblin_warrior(const std::string& name, uint16_t health, uint16_t attack_damage, uint16_t ability_power);
    };
}
