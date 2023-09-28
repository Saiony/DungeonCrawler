#include "gameplay_state_model.h"

dungeon_common::model::gameplay_state_model::gameplay_state_model() = default;

dungeon_common::model::gameplay_state_model::gameplay_state_model(const enums::gameplay_state_type state) : state(state)
{
}
