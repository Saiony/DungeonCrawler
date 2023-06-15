#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class bite_action final : public base_action
    {
    public:
        std::string target_id;
        
        ~bite_action() override;
        bite_action(const dungeon_common::model::action_types& action_type, std::string target_id);
        void use(const std::shared_ptr<encounter>& encounter_ptr) override;
    };
}