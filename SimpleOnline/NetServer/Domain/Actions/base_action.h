#pragma once
#include <iostream>

#include "Models/action_model.h"

namespace domain::action
{
    class base_action
    {
    public:
        virtual ~base_action() = default;
        action_types id;
        int target_id{};

        explicit base_action(action_model model);
        virtual void use()
        {
            std::cout << "base use " << std::endl;
        }
    };
}
