#include <utility>

#include "player_factory.h"

std::shared_ptr<dungeon_server::domain::player> dungeon_server::domain::action::player_factory::create_player
                                                (std::string player_id, const std::string& player_name, class_type class_type)
{
    std::vector<dungeon_common::model::action_types> actions;
    actions.push_back(dungeon_common::model::action_types::sword_slash);
    actions.push_back(dungeon_common::model::action_types::heal);
    
    player player(std::move(player_id), player_name, 10, 7, 5, actions);
    return std::make_shared<class player>(player);
}
