#include "action_factory.h"

#include "NetServer/Domain/Actions/heal_action.h"
#include "NetServer/Domain/Actions/sword_slash_action.h"

std::shared_ptr<domain::action::base_action> domain::action::action_factory::create_action(
                                                                                    dungeon_common::model::action_model action_model,
                                                                                    std::shared_ptr<dungeon_server::domain::encounter::encounter>& encounter_ptr)

{
    switch (action_model.id)
    {
    case (dungeon_common::model::action_types::sword_slash):
        {
            return std::make_shared<sword_slash_action>(action_model, encounter_ptr);
        }
        case(dungeon_common::model::action_types::heal):
        {
            return std::make_shared<heal_action>(action_model, encounter_ptr);
        }
    default :
        {
            return std::make_shared<sword_slash_action>(action_model, encounter_ptr);            
        }
    }
}
