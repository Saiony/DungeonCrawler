#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class concentrating_status : public base_creature_status
    {
    public:
        dungeon_common::enums::creature_status_type get_type() override;
        void on_after_attack(const std::shared_ptr<encounter>& encounter, const std::string& attacked_creature_id, std::string& action_log) override;
        int16_t get_attack_multiplier() override;
    };
}