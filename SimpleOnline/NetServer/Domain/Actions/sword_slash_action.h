#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class sword_slash_action final : public base_action
    {
    public:
        explicit sword_slash_action(const dungeon_common::model::action_model& model)
                             : base_action(model)
        {
        }

        ~sword_slash_action() override;
        void use(const std::shared_ptr<encounter>& encounter_ptr) override;
    };
}