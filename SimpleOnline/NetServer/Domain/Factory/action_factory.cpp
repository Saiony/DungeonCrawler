#include "action_factory.h"

#include "NetServer/Domain/Actions/fire_at_will_action.h"
#include "NetServer/Domain/Actions/heal_action.h"
#include "NetServer/Domain/Actions/holy_light.h"
#include "NetServer/Domain/Actions/pet_the_eagle_action.h"
#include "NetServer/Domain/Actions/provoke_action.h"
#include "NetServer/Domain/Actions/shield_bash.h"
#include "NetServer/Domain/Actions/sword_slash_action.h"

std::shared_ptr<dungeon_server::domain::action::base_action> dungeon_server::domain::factory::action_factory::create_action
(dungeon_common::model::action_use_model action_model)
{
    const auto target_id = std::string(std::begin(action_model.target_id), std::end(action_model.target_id));
    const auto owner_id = std::string(std::begin(action_model.owner_id), std::end(action_model.owner_id));

    return create_action(action_model.id, owner_id, target_id);
}

std::shared_ptr<dungeon_server::domain::action::base_action> dungeon_server::domain::factory::action_factory::create_action
(dungeon_common::model::action_types action_type, const std::string& owner_id, const std::string& target_id)
{
    switch (action_type)
    {
    case (dungeon_common::model::action_types::sword_slash):
        {
            return std::make_shared<action::sword_slash_action>(action_type, owner_id, target_id);
        }
    case (dungeon_common::model::action_types::heal):
        {
            return std::make_shared<action::heal_action>(action_type, owner_id, target_id);
        }
    case(dungeon_common::model::action_types::shield_bash):
        {
            return std::make_shared<action::shield_bash>(action_type, owner_id, target_id);
        }
    case(dungeon_common::model::action_types::holy_light):
        {
            return std::make_shared<action::holy_light>(action_type, owner_id, target_id);
        }
    case(dungeon_common::model::action_types::fire_at_will):
        {
            return std::make_shared<action::fire_at_will_action>(action_type, owner_id);
        }
    case(dungeon_common::model::action_types::pet_the_eagle):
        {
            return std::make_shared<action::pet_the_eagle_action>(action_type, owner_id);
        }
    case(dungeon_common::model::action_types::provoke):
        {
            return std::make_shared<action::provoke_action>(action_type, owner_id);
        }
    default:
        {
            return std::make_shared<action::sword_slash_action>(action_type, owner_id, target_id);
        }
    }
}
