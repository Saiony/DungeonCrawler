#pragma once
#include "base_enemy.h"

namespace dungeon_server::domain::enemy
{
    class giant_spider final : public base_enemy
    {
    protected:
        void on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, action_log& action_log) override;
    public:
        giant_spider(uint16_t health, uint16_t attack_damage, uint16_t ability_power);
        void on_died(const std::shared_ptr<encounter>& encounter, action_log& action_log) override;
        std::string get_base_name() override;
    };
}
