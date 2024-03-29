﻿#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class frostbite_action final : public base_action
    {
    private:
        std::string target_id_{};
        const std::uint16_t freeze_chance_ = 100.0f; 
        
    public:
        frostbite_action(const dungeon_common::model::action_types& action_type, const std::string& new_action_owner_id, std::string target_id);
        ~frostbite_action() override;

        std::string get_name() override;
        std::uint8_t get_targets_count() override;
        enums::offensive_stats_type get_offensive_stat_type() override;
        float_t get_damage_variance() override;
        float_t get_offensive_stat_multiplier() override;
        
        void use(const std::shared_ptr<encounter>& encounter_ptr, action_log& action_log) override;
    };
}
