#include "bonfire_story_result_model.h"
#include "../../NetServer/Domain/action_log.h"

dungeon_common::model::bonfire_story_result_model::bonfire_story_result_model() = default;

dungeon_common::model::bonfire_story_result_model::bonfire_story_result_model(const bonfire_story_model& bonfire_story,
                                                                              const player_model& story_teller,
                                                                              std::string story_string)
    : bonfire_story(bonfire_story), story_teller(story_teller)
{
    std::ranges::copy(story_string, story);
}
