#pragma once
#include "action_use_model.h"

struct player_action_model
{
    dungeon_common::model::action_types id{};
    char name[40]{};
    uint8_t targets_number{};

    player_action_model();
    player_action_model(const dungeon_common::model::action_types id, std::string new_name, uint8_t targets_number);
};
