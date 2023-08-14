#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include "player_action_model.h"
#include "player_classes_model.h"

namespace dungeon_common::model
{
    struct player_config_model
    {
        char id[39]{};
        char name[40]{};
        player_class_model player_class;
        uint32_t max_health{};
        uint16_t attack_damage{};
        uint16_t ability_power{};
        std::array<player_action_model, 4> actions{};

        player_config_model();
        player_config_model(const std::string& new_id, const std::string& new_name, const player_class_model player_class,
                            const uint16_t health, const uint16_t attack_damage, const uint16_t ability_power,
                            const std::vector<player_action_model>& action_list);   
    };
}
