#pragma once
#include "base_action.h"

namespace domain::action
{
    class heal_action final : public base_action
    {
    public:
        explicit heal_action(const action_model& model): base_action(model)
        {
        }

        ~heal_action() override;
        void use() override;
    };
}
