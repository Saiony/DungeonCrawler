#pragma once
#include "Models/action_model.h"
#include "NetServer/Domain/Actions/base_action.h"

namespace domain::action
{
     class action_factory
     {
     public:
          static std::shared_ptr<domain::action::base_action> create_action(action_model action_model);
     };
}