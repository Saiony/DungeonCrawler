#pragma once
#include "player_model.h"
#include "../base_client.h"

namespace dungeon_common::model
{
    struct enemy_model
    {
        char id[40]{};
        char name[40]{};
        uint16_t health;

        enemy_model(std::string new_id, std::string name_string, uint16_t health);
        enemy_model();
    };
    
    struct encounter_model
    {
        std::array<enemy_model, 3> enemies{};
        std::array<player_model, 3> players{};

        encounter_model() = default;
    };
}
