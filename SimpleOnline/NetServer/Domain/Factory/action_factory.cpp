#include "action_factory.h"

#include "NetServer/Domain/Actions/heal_action.h"
#include "NetServer/Domain/Actions/sword_slash_action.h"

std::shared_ptr<domain::action::base_action> domain::action::action_factory::create_action(action_model action_model)
{
    switch (action_model.id)
    {
    case (action_types::sword_slash):
        {
            return std::make_shared<sword_slash_action>(action_model);
        }
        case(action_types::heal):
        {
            return std::make_shared<heal_action>(action_model);
        }
    default :
        {
            return std::make_shared<sword_slash_action>(action_model);            
        }
    }
}
