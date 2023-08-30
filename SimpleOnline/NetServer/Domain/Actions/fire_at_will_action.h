#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class fire_at_will_action final : public base_action
    {
    private:
        const float_t variance_ = 0.3f;
        const float_t dmg_multiplier_ = 0.5f;
    public:
        explicit fire_at_will_action(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id);
        ~fire_at_will_action() override;

        std::string get_name() override;
        std::uint8_t get_targets_count() override{ return 0; }
        std::string use(const std::shared_ptr<encounter>& encounter_ptr) override;
    };
}
