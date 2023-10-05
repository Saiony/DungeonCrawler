#pragma once

#include "creature_stats_model.h"
#include "player_model.h"

namespace dungeon_common::model
{
    struct bonfire_result_model
    {
        player_model story_teller{};
        creature_stats_model upgraded_stat{};
        std::array<char[250], 10> level_up_log{};
        char story[250]{};

        bonfire_result_model();
        bonfire_result_model(const player_model& story_teller, creature_stats_model upgraded_stat, std::string story_string);
    };
}
