#include "bonfire_story_teller_model.h"

#include <algorithm>

dungeon_common::model::bonfire_story_teller_model::bonfire_story_teller_model(const player_model& player_model, const uint16_t max_characters,
                                                                              std::vector<creature_stats_model> stats)
    : story_teller(player_model), max_characters(max_characters)
{
    std::ranges::transform(stats, std::begin(player_stats), [](const auto& x) { return x; });
}
