#pragma once
#include "player_model.h"
#include "../base_client.h"

namespace dungeon_common::model
{
    struct enemy_model
    {
        char id[39]{};
        char name[40]{};
        uint16_t health;
        uint16_t max_health;

        enemy_model(std::string new_id, std::string name_string, uint16_t health, uint16_t max_health);
        enemy_model();
    };
    
    struct encounter_model
    {
        std::array<enemy_model, 10> enemies{};
        std::array<player_model, 3> players{};
        char active_creature_id[39]{};
        std::array<char[250], 20> log{};
        bool game_over{};
        bool players_won{};

        encounter_model() = default;
    };
}
