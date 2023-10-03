#pragma once
#include <string>

#include "../Enum/creature_stat_types.h"

namespace dungeon_common::model
{
    struct bonfire_story_model
    {
        enums::creature_stat_types stat_id{};
        char story[250]{};

        bonfire_story_model();
        bonfire_story_model(enums::creature_stat_types stat_id, const std::string& story_string);
    };
}