#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include "player_action_model.h"

namespace dungeon_common::model
{
    struct player_config_model
    {
        char id[39]{};
        char name[40]{};
        uint32_t max_health{};
        std::array<player_action_model, 4> actions{};

        player_config_model();
        player_config_model(const std::string& new_id, const std::string& new_name, uint32_t health, const std::vector<player_action_model>& action_list);   
    };
}