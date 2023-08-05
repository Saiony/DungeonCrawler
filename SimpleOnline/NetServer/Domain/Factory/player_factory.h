#pragma once
#include <memory>

#include "NetServer/Domain/Player.h"

namespace dungeon_server::domain::action
{
    class player_factory
    {
    public:
        static std::shared_ptr<player> create_player(std::string player_id, const std::string& player_name, class_type class_type);
    };
}
