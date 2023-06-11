#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class heal_action final : public base_action
    {
    public:
        explicit heal_action(const dungeon_common::model::action_model& model)
                             : base_action(model)
        {
        }

        ~heal_action() override;
        void use(const std::shared_ptr<domain::encounter>& encounter_ptr) override;
    };
}
