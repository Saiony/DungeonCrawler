#include "action_factory.h"
#include "NetServer/Domain/Actions/sword_slash_action.h"

std::shared_ptr<dungeon_server::domain::action::base_action> dungeon_server::domain::action::action_factory::create_action(dungeon_common::model::action_model action_model)
{
    switch (action_model.id)
    {
    case (dungeon_common::model::action_types::sword_slash):
        {
            auto target_id = std::string(std::begin(action_model.target_id), std::end(action_model.target_id));
            auto owner_id = std::string(std::begin(action_model.owner_id), std::end(action_model.owner_id));
            return std::make_shared<sword_slash_action>(action_model.id, owner_id, target_id);
        }
    default :
        {
            return std::make_shared<sword_slash_action>(action_model.id, action_model.owner_id,action_model.target_id);            
        }
    }
}
