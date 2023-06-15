﻿#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class heal_action final : public base_action
    {
    public:
        std::string target_id;
        
        explicit heal_action(const dungeon_common::model::action_types& action_type, std::string target_id);
        ~heal_action() override;
        void use(const std::shared_ptr<encounter>& encounter_ptr) override;
    };
}
