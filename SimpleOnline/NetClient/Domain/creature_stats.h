#pragma once
#include "creature_stat_types.h"
#include "Player.h"

namespace dungeon_client::domain
{
    class creature_stats
    {
    public:
        dungeon_common::enums::creature_stat_types id{};
        std::string name{};

        creature_stats();
        creature_stats(dungeon_common::enums::creature_stat_types id, std::string name);
    };
}