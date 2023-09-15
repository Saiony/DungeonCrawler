#include "action_factory.h"

#include "NetServer/Domain/Actions/aegis_of_faith_action.h"
#include "NetServer/Domain/Actions/arcane_blast_action.h"
#include "NetServer/Domain/Actions/celestial_weakening_action.h"
#include "NetServer/Domain/Actions/concentrate_action.h"
#include "NetServer/Domain/Actions/fireball_action.h"
#include "NetServer/Domain/Actions/fire_at_will_action.h"
#include "NetServer/Domain/Actions/frostbite_action.h"
#include "NetServer/Domain/Actions/heal_action.h"
#include "NetServer/Domain/Actions/holy_light.h"
#include "NetServer/Domain/Actions/pet_the_eagle_action.h"
#include "NetServer/Domain/Actions/provoke_action.h"
#include "NetServer/Domain/Actions/retribution_action.h"
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
    case dungeon_common::model::action_types::concentrate:
        {
            return std::make_shared<action::concentrate_action>(action_type, owner_id);
        }
    case dungeon_common::model::action_types::fireball:
        {
            return std::make_shared<action::fireball_action>(action_type, owner_id, target_id);
        }
    case dungeon_common::model::action_types::frostbite:
        {
            return std::make_shared<action::frostbite_action>(action_type, owner_id, target_id);
        }
    case dungeon_common::model::action_types::arcane_blast:
        {
            return std::make_shared<action::arcane_blast_action>(action_type, owner_id, target_id);
        }
    case dungeon_common::model::action_types::retribution:
        {
            return std::make_shared<action::retribution_action>(action_type, owner_id);
        }
    case dungeon_common::model::action_types::celestial_weakening:
        {
            return std::make_shared<action::celestial_weakening_action>(action_type, owner_id, target_id);
        }
    case dungeon_common::model::action_types::aegis_of_faith:
        {
            return std::make_shared<action::aegis_of_faith_action>(action_type, owner_id, target_id);
        }
    default:
        {
            return nullptr;
        }
    }
}
