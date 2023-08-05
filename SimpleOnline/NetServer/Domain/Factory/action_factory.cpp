#include "action_factory.h"

#include "NetServer/Domain/Actions/heal_action.h"
#include "NetServer/Domain/Actions/sword_slash_action.h"

std::shared_ptr<dungeon_server::domain::action::base_action> dungeon_server::domain::action::action_factory::create_action
    (dungeon_common::model::action_use_model action_model)
{
    const auto target_id = std::string(std::begin(action_model.target_id), std::end(action_model.target_id));
    const auto owner_id = std::string(std::begin(action_model.owner_id), std::end(action_model.owner_id));
    
    return create_action(action_model.id, owner_id, target_id);
}

std::shared_ptr<dungeon_server::domain::action::base_action> dungeon_server::domain::action::action_factory::create_action
    (dungeon_common::model::action_types action_type, const std::string& owner_id, const std::string& target_id)
{ 
    switch (action_type)
    {
    case (dungeon_common::model::action_types::sword_slash):
        {
            return std::make_shared<sword_slash_action>(action_type, owner_id, target_id);
        }
    case (dungeon_common::model::action_types::heal):
        {
            return std::make_shared<heal_action>(action_type, owner_id, target_id);
        }
    default :
        {
            return std::make_shared<sword_slash_action>(action_type, owner_id, target_id);
        }
    }
}
