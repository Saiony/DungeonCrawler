#include "provoke_action.h"

#include "NetServer/Domain/Status/provoking_status.h"

dungeon_server::domain::action::provoke_action::provoke_action(const dungeon_common::model::action_types& action_type,
                                                               const std::string& new_action_owner_id)
                                                               : base_action(action_type, new_action_owner_id)
{
}

dungeon_server::domain::action::provoke_action::~provoke_action() = default;

std::string dungeon_server::domain::action::provoke_action::get_name()
{
    return "provoke";
}

std::uint8_t dungeon_server::domain::action::provoke_action::get_targets_count()
{
    return 0;
}

std::string dungeon_server::domain::action::provoke_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    action_owner->add_status(std::make_shared<provoking_status>(dungeon_common::enums::creature_status_type::provoking, 3, action_owner_id, encounter_ptr));

    return "\n" + action_owner->name + " used " + get_name() + ". Aggro is raised for 3 turns";
}
