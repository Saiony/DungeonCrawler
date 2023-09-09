#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class shield_bash final : public base_action
    {
    private:
        const float_t variance_ = 0.2f;
        const float_t dmg_multiplier_ = 0.5;
    public:
        std::string target_id{};
        
        ~shield_bash() override = default;
        explicit shield_bash(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id, std::string target_id = {});
        std::string get_name() override;
        std::uint8_t get_targets_count() override;
        void use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) override;
    };
}
