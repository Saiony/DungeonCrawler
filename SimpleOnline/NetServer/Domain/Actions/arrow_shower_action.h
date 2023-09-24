#pragma once
#include "base_action.h"
#include "Enum/action_target_types.h"

namespace dungeon_server::domain::action
{
    class arrow_shower_action final : public base_action
    {
    private:
        dungeon_common::enums::action_target_types target_type_;
        
    public:
        arrow_shower_action(const dungeon_common::model::action_types& action_type,
                            const std::string& new_action_owner_id,
                            dungeon_common::enums::action_target_types target_type);
        ~arrow_shower_action() override;
        std::string get_name() override;
        std::uint8_t get_targets_count() override;
        enums::offensive_stats_type get_offensive_stat_type() override;
        float_t get_damage_variance() override;
        float_t get_offensive_stat_multiplier() override;
        
        void use(const std::shared_ptr<encounter>& encounter_ptr, action_log& action_log) override;
        void shoot_arrow(const std::shared_ptr<encounter>& encounter,
                         const std::shared_ptr<base_creature>& action_owner,
                         const std::shared_ptr<base_creature>& target,
                         action_log& action_log);
    };
}
