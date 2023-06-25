#include "action.h"

dungeon_client::domain::action::action() : id(dungeon_common::model::action_types::unknown)
{    
}

dungeon_client::domain::action::action(const dungeon_common::model::action_types id, std::string name) : id(id), name(std::move(name))
{
}
