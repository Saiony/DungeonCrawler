#pragma once
#include "action_target_types.h"
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class arrow_shower_action final : public base_action
    {
    private:
        const float_t variance_ = 0.5f;
        dungeon_common::enums::action_target_types target_type_;
    public:
        arrow_shower_action(const dungeon_common::model::action_types& action_type,
                            const std::string& new_action_owner_id,
                            dungeon_common::enums::action_target_types target_type);
        ~arrow_shower_action() override;
        std::string get_name() override;
        std::uint8_t get_targets_count() override;
        std::string use(const std::shared_ptr<encounter>& encounter_ptr) override;
        std::string shoot_arrow(const std::shared_ptr<encounter>& encounter, const std::shared_ptr<base_creature>& action_owner,
                                const std::shared_ptr<base_creature>& target);
    };
}
