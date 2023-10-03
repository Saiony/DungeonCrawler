#pragma once
#include <vector>

#include "creature_stats.h"
#include "Player.h"

namespace dungeon_client::domain
{  
    class bonfire_story_telling
    {
    public:
        player story_teller;
        uint16_t max_characters;
        std::vector<creature_stats> player_stats;

        bonfire_story_telling(player story_teller, uint16_t max_characters, std::vector<creature_stats> player_stats);
    };
}
