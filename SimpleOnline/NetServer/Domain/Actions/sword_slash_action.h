#pragma once
#include "base_action.h"

namespace dungeon_server::domain::action
{
    class sword_slash_action final : public base_action
    {
    public:
        explicit sword_slash_action(const dungeon_common::model::action_model& model, std::shared_ptr<domain::encounter>& encounter_ptr)
                             : base_action(model, encounter_ptr)
        {
        }

        ~sword_slash_action() override;
        void use() override;
    };
}