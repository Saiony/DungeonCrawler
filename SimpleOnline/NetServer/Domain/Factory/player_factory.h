#pragma once
#include <memory>

#include "Enum/player_class_types.h"
#include "NetServer/Domain/Player.h"

namespace dungeon_server::domain::factory
{
    class player_factory
    {
    public:
        static std::shared_ptr<player> create_player(const std::string& player_id, const std::string& player_name, const dungeon_common::enums::player_class_type player_class_id);
    };
}
