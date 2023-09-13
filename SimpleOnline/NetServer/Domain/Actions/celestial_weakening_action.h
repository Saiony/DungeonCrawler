#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class celestial_weakening_action final : public base_action
    {
    public:
        celestial_weakening_action(const dungeon_common::model::action_types& action_type, const std::string& new_action_owner_id);

        ~celestial_weakening_action() override;
        std::string get_name() override;
        enums::offensive_stats_type get_offensive_stat_type() override;
        std::uint8_t get_targets_count() override;
        float_t get_damage_variance() override;
        float_t get_offensive_stat_multiplier() override;
        void use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) override;
    };
}
