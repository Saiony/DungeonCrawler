#pragma once
#include "player_model.h"
#include "../base_client.h"
#include "../../NetServer/Domain/Encounter.h"

namespace dungeon_common::model
{
    struct enemy_model
    {
        char name[40]{};
        uint16_t health;

        enemy_model(std::string name_string, uint16_t health);
        enemy_model();
    };
    
    struct encounter_model
    {
        std::array<enemy_model, 3> enemies{};
        std::array<player_model, 3> players{};

        encounter_model() = default;
    };
}
