#pragma once
#include "base_enemy.h"

namespace dungeon_server::domain::enemy
{
    class goblin_archer final : public base_enemy
    {
    protected:
        void on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) override;
    public:
        goblin_archer(uint16_t health, uint16_t attack_damage, uint16_t ability_power);
        std::string get_base_name() override;
    };
}
