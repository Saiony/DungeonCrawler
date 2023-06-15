#include "action_factory.h"
#include "NetServer/Domain/Actions/heal_action.h"
#include "NetServer/Domain/Actions/sword_slash_action.h"

std::shared_ptr<dungeon_server::domain::action::base_action> dungeon_server::domain::action::action_factory::create_action(dungeon_common::model::action_model action_model)
{
    switch (action_model.id)
    {
    case (dungeon_common::model::action_types::sword_slash):
        {
            auto x = std::string(std::begin(action_model.target_id), std::end(action_model.target_id));
            return std::make_shared<sword_slash_action>(action_model.id, x);
        }
        case(dungeon_common::model::action_types::heal):
        {
            return std::make_shared<heal_action>(action_model.id, action_model.target_id);
        }
    default :
        {
            return std::make_shared<sword_slash_action>(action_model.id, action_model.target_id);            
        }
    }
}
