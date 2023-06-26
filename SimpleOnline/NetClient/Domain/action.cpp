#include "action.h"

dungeon_client::domain::action::action() : id(dungeon_common::model::action_types::unknown)
{    
}

dungeon_client::domain::action::action(const dungeon_common::model::action_types id, std::string name, const uint8_t targets_count)
                                       : id(id), name(std::move(name)), targets_count(targets_count)
{
}

bool dungeon_client::domain::action::needs_target() const
{
    return targets_count > 0;
}
