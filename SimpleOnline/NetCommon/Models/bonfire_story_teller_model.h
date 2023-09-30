#pragma once

#include "player_model.h"

namespace dungeon_common::model
{
    class bonfire_story_teller_model
    {
    public:
        player_model story_teller{};
        
        bonfire_story_teller_model() = default;
        explicit bonfire_story_teller_model(const player_model& player_model);
    };
}
