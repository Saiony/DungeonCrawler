#include "bonfire_story_model.h"

dungeon_common::model::bonfire_story_model::bonfire_story_model() = default;

dungeon_common::model::bonfire_story_model::bonfire_story_model(const enums::creature_stat_types stat_id, const std::string& story_string)
    : stat_id(stat_id)
{
    std::ranges::copy(story_string, story);
}
