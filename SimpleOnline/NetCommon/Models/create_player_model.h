#pragma once
#include <string>

#include "../Enum/player_class_types.h"

namespace dungeon_common::model
{
    class create_player_model
    {
    public:
        char name[40]{};
        enums::player_class_type player_class_type{};

        create_player_model() = default;
        create_player_model(const std::string& name_string, const enums::player_class_type player_class_type);
    };
}