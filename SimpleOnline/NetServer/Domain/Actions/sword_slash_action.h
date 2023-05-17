#pragma once
#include "base_action.h"

namespace domain::action
{
    class sword_slash_action final : public base_action
    {
    public:
        explicit sword_slash_action(const action_model& model) : base_action(model)
        {
        }

        ~sword_slash_action() override;
        void use() override;
    };
}