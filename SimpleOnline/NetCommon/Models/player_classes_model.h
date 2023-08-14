#pragma once
#include <array>
#include <string>

#include "../Enum/player_class_types.h"

namespace dungeon_common::model
{
    class player_class_model
    {
    public:
        enums::player_class_type id{};
        char name[40]{};

        player_class_model() = default;
        player_class_model(const enums::player_class_type id, std::string name_string) : id(id)
        {
            std::copy(std::begin(name_string), std::end(name_string), name);
        }
    };
    
    class player_classes_model
    {
    public:
        std::array<player_class_model, 3> classes;
    };
}
