#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class heal_action final : public base_action
    {
    private:
        const float_t variance_ = 0.2f;
    public:
        std::string target_id;
        
        heal_action(const dungeon_common::model::action_types& action_type, const std::string& new_action_owner_id, std::string target_id);
        ~heal_action() override;
        std::string get_name() override;
        std::string use(const std::shared_ptr<encounter>& encounter_ptr) override;
        std::uint8_t get_targets_count() override{ return 1; }
    };
}
