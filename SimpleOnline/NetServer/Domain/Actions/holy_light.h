#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class holy_light final : public base_action
    {
    public:
        std::string target_id{};
        
        explicit holy_light(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id, std::string target_id = {});
        ~holy_light() override;
        
        enums::offensive_stats_type get_offensive_stat_type() override;
        float_t get_damage_variance() override;
        float_t get_offensive_stat_multiplier() override;
        std::string get_name() override;
        std::uint8_t get_targets_count() override{ return 1; }
        void use(const std::shared_ptr<encounter>& encounter_ptr, action_log& action_log) override;
    };
}