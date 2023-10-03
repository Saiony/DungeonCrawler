#include "bonfire_story_telling.h"

dungeon_client::domain::bonfire_story_telling::bonfire_story_telling(player story_teller,
                                                                     const uint16_t max_characters,
                                                                     std::vector<creature_stats> player_stats)
    : story_teller(std::move(story_teller)),
      max_characters(max_characters),
      player_stats(std::move(player_stats))
{
}

