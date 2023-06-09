﻿#include "encounter_model.h"

dungeon_common::model::enemy_model::enemy_model(std::string new_id, std::string name_string, const uint16_t health): health(health)
{
    std::ranges::copy(name_string, name);
    std::ranges::copy(new_id, id);
}

dungeon_common::model::enemy_model::enemy_model() : health(-1)
{
}
