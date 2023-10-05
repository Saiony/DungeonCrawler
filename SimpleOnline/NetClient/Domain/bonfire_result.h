#pragma once

#include <list>
#include "creature_stats.h"
#include "Player.h"

namespace dungeon_client::domain
{
    class bonfire_result
    {
    public:
        player story_teller;
        creature_stats upgraded_stat;
        std::list<std::string> level_up_log;
        std::string story{};
        
        bonfire_result(player story_teller, creature_stats upgraded_stat, std::list<std::string> level_up_log,
                       std::string story);
    };
}
