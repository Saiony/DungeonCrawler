﻿#pragma once
#include <string>

namespace dungeon_common::model
{
    enum class action_types
    {
        unknown = 0,
        sword_slash,
        heal,
        bite,
    };

    struct action_use_model
    {
        action_types id;
        char target_id[39]{};
        char owner_id[39]{};

        action_use_model(action_types id, const std::string& new_owner_id, const std::string& new_target_id);
        action_use_model();
    };
}
