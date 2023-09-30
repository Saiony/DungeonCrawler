#pragma once

namespace dungeon_common::enums
{
    enum class gameplay_state_type
    {
        unknown = 0,
        combat,
        story,
        bonfire,
        game_over_win,
        game_over_loss,
    };
}