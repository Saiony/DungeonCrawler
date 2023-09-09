#include "concentrate_action.h"

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

std::uint8_t dungeon_server::domain::action::concentrate_action::get_targets_count()
{
    return 0;
}

void dungeon_server::domain::action::concentrate_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
}