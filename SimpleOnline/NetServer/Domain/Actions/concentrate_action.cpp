#include <memory>
#include "concentrate_action.h"

#include "NetServer/Domain/Status/concentrating_status.h"

dungeon_server::domain::action::concentrate_action::concentrate_action(const dungeon_common::model::action_types& action_type,
                                                                       const std::string& new_action_owner_id)
    : base_action(action_type, new_action_owner_id)
{
}

dungeon_server::domain::action::concentrate_action::~concentrate_action() = default;

std::string dungeon_server::domain::action::concentrate_action::get_name()
{
    return "concentrate";
}

uint8_t dungeon_server::domain::action::concentrate_action::get_targets_count()
{
    return 0;
}

void dungeon_server::domain::action::concentrate_action::use(const std::shared_ptr<encounter>& encounter_ptr, action_log& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto status = action_owner->add_status(std::make_shared<concentrating_status>(action_owner_id));

    action_log.add_log(action_owner->name + " used " + get_name() + " - Stacks: " + std::to_string(status->quantity));
}
