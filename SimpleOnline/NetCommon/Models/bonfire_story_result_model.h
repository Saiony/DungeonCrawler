#pragma once
#include <list>

#include "bonfire_story_model.h"
#include "player_model.h"

namespace dungeon_common::model
{
    struct bonfire_story_result_model
    {
        bonfire_story_model bonfire_story;
        player_model story_teller{};
        std::array<char[250], 10> level_up_log{};
        char story[250]{};

        bonfire_story_result_model();
        bonfire_story_result_model(const bonfire_story_model& bonfire_story, const player_model& story_teller, std::string story_string);
    };
}