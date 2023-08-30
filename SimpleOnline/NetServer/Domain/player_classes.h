#pragma once
#include <string>
#include <vector>

#include "Enum/player_class_types.h"

namespace dungeon_server::domain
{
    class player_class
    {
    public:
        dungeon_common::enums::player_class_type id;
        std::string name;

        player_class(const dungeon_common::enums::player_class_type id, std::string name_string) : id(id), name(std::move(name_string))
        {            
        }
    };
    
    class player_classes
    {
    public:
        std::vector<player_class> classes;

        player_classes()
        {
            classes =
            {
                {dungeon_common::enums::player_class_type::warrior, "warrior"},
                {dungeon_common::enums::player_class_type::cleric, "cleric"},
                {dungeon_common::enums::player_class_type::archer, "archer"},
            };
        }

        player_class get_class(const dungeon_common::enums::player_class_type class_type)
        {
            const auto it = std::ranges::find_if(classes, [class_type](auto player_class)
            {
                return player_class.id == class_type;
            });

            return *it;
        }
    };
}
