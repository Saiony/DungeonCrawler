#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class arrow_shot_action final : public base_action
    {
    private:
        const float_t variance_ = 0.5f;
        std::string target_id_;
    public:

        arrow_shot_action(const dungeon_common::model::action_types& action_type, const std::string& new_action_owner_id, std::string target_id);
        ~arrow_shot_action() override;
        
        std::string get_name() override;
        std::uint8_t get_targets_count() override;
        std::string use(const std::shared_ptr<encounter>& encounter_ptr) override;
    };
}
