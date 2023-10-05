#include "bonfire_result.h"

#include <utility>

dungeon_client::domain::bonfire_result::bonfire_result(player story_teller, creature_stats upgraded_stat,
                                                       std::list<std::string> level_up_log, std::string story)
    : story_teller(std::move(story_teller)),
      upgraded_stat(std::move(upgraded_stat)),
      level_up_log(std::move(level_up_log)),
      story(std::move(story))
{
}
