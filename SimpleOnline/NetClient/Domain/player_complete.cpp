#include "player_complete.h"

#include <memory>

dungeon_client::domain::player_complete::player_complete(const std::string& id, const std::string& name, const uint32_t health, const std::array<action, 4> actions)
                                                        : player(id, name, health), actions(actions)
{
}

std::shared_ptr<dungeon_client::domain::action> dungeon_client::domain::player_complete::get_action(dungeon_common::model::action_types action_id)
{
    const auto action_it = std::ranges::find_if(actions, [&action_id](auto action) { return action.id == action_id; });
    return action_it != std::end(actions) ? std::make_shared<action>(*action_it) : nullptr; 
}

std::shared_ptr<dungeon_client::domain::action> dungeon_client::domain::player_complete::get_action(std::string action_name)
{
    const auto action_it = std::ranges::find_if(actions, [&action_name](auto action) { return action.name == action_name; });
    return action_it != std::end(actions) ? std::make_shared<action>(*action_it) : nullptr; 
}