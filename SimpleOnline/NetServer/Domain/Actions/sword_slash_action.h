#pragma once
#include "base_action.h"

namespace domain::action
{
    class sword_slash_action final : public base_action
    {
    public:
        explicit sword_slash_action(const dungeon_common::model::action_model& model, std::shared_ptr<dungeon_server::domain::encounter::encounter>& encounter_ptr)
                             : base_action(model, encounter_ptr)
        {
        }

        ~sword_slash_action() override;
        void use() override;
    };
}