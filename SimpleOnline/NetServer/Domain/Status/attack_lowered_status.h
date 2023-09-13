#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class attack_lowered_status final : public base_creature_status
    {
    private:
        const int16_t debuff_value_ = 2;
        
    public:
        attack_lowered_status(const std::string& creature_id, const std::shared_ptr<encounter>& encounter_ptr, const uint8_t duration);

        dungeon_common::enums::creature_status_type get_type() override;
        void on_overriding_status_added(std::shared_ptr<base_creature_status> status) override;
        void on_end_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log) override;
    };
}
