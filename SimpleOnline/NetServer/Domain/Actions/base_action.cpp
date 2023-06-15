#include "base_action.h"

dungeon_server::domain::action::base_action::~base_action() = default;

dungeon_server::domain::action::base_action::base_action(const dungeon_common::model::action_types& action_type) : id(action_type)
{
}
