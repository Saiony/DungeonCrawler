#pragma once
#include "../Enum/gameplay_state_type.h"

namespace dungeon_common::model
{
    struct gameplay_state_model
    {
        enums::gameplay_state_type state{};

        gameplay_state_model();
        explicit gameplay_state_model(enums::gameplay_state_type state);
    };
}
