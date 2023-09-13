#include "aegis_of_faith_action.h"

dungeon_server::domain::action::aegis_of_faith_action::aegis_of_faith_action(const dungeon_common::model::action_types& action_type,
                                                                             const std::string& new_action_owner_id)
    : base_action(action_type, new_action_owner_id)
{
}

dungeon_server::domain::action::aegis_of_faith_action::~aegis_of_faith_action() = default;

std::string dungeon_server::domain::action::aegis_of_faith_action::get_name()
{
    return "aegis of faith";
}

std::uint8_t dungeon_server::domain::action::aegis_of_faith_action::get_targets_count()
{
    return 1;
}

void dungeon_server::domain::action::aegis_of_faith_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    
}
