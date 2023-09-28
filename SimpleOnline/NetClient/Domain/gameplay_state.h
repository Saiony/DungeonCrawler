#pragma once
#include "gameplay_state_type.h"

namespace dungeon_client::domain
{
     class gameplay_state
     {
     public:
          dungeon_common::enums::gameplay_state_type state;

          explicit gameplay_state(dungeon_common::enums::gameplay_state_type state);
     };
}
