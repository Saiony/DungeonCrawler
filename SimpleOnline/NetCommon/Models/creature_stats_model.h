#pragma once
#include <string>

#include "../Enum/creature_stat_types.h"

class creature_stats_model
{
public:
    dungeon_common::enums::creature_stat_types id{};
    char name[40]{};

    creature_stats_model();
    creature_stats_model(dungeon_common::enums::creature_stat_types id, std::string name_string);
};
