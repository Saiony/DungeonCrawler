#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class sword_slash_action final : public base_action
    {
    public:
        std::string target_id{};
        
        ~sword_slash_action() override;
        explicit sword_slash_action(const dungeon_common::model::action_types& action_type, std::string new_target_id);
        void use(const std::shared_ptr<encounter>& encounter_ptr) override;
    };
}