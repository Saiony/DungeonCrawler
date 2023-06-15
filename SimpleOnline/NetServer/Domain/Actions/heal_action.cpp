#include "heal_action.h"

dungeon_server::domain::action::heal_action::~heal_action() = default;

dungeon_server::domain::action::heal_action::heal_action(const dungeon_common::model::action_types& action_type, std::string target_id)
                                                        : base_action(action_type), target_id(std::move(target_id))
{
}


void dungeon_server::domain::action::heal_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
 
}
