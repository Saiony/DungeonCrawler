#pragma once
#include <string>

#include "creature_stat_types.h"

class creature_stat
{
public:
    dungeon_common::enums::creature_stat_types id{};
    std::string name{};

    creature_stat();
    creature_stat(dungeon_common::enums::creature_stat_types id, std::string name);
};
