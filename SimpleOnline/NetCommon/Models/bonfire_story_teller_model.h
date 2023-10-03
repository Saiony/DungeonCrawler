#pragma once

#include <vector>

#include "creature_stats_model.h"
#include "player_model.h"

namespace dungeon_common::model
{
    struct bonfire_story_teller_model
    {
    public:
        player_model story_teller{};
        uint16_t max_characters{};
        std::array<creature_stats_model, 3> player_stats{}; 

        bonfire_story_teller_model() = default;
        explicit bonfire_story_teller_model(const player_model& player_model, uint16_t max_characters,
                                            std::vector<creature_stats_model> stats);
    };
}
