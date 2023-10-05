#include "bonfire_result_model.h"

dungeon_common::model::bonfire_result_model::bonfire_result_model() = default;

dungeon_common::model::bonfire_result_model::bonfire_result_model(const player_model& story_teller,
                                                                  const creature_stats_model upgraded_stat,
                                                                  std::string story_string)
    : story_teller(story_teller), upgraded_stat(upgraded_stat)
{
    std::ranges::copy(story_string, story);
}
