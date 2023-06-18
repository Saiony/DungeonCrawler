#include "base_action.h"

#include <utility>

dungeon_server::domain::action::base_action::~base_action() = default;

dungeon_server::domain::action::base_action::base_action(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id)
                                                        : id(action_type), action_owner_id(std::move(new_action_owner_id))
{
}
