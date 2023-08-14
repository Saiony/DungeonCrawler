#pragma once
#include <string>

#include "Enum/player_class_types.h"

namespace dungeon_client::domain
{
    class player_class
    {
    public:
        dungeon_common::enums::player_class_type id{};
        std::string name;

        player_class();
        player_class(dungeon_common::enums::player_class_type id, std::string name);
    };
}