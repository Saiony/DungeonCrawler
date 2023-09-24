#pragma once
#include <array>

namespace dungeon_common::model
{
    struct story_model
    {
        std::array<char[250], 20> story{};
    };
}