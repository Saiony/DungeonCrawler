#pragma once
#include <cstdint>
#include <string>

namespace dungeon_common::model
{
    class player_model
    {
    public:
        char id[40]{};
        char name[40]{};
        uint32_t health{};
        
        player_model();
        player_model(std::string new_id, std::string new_name, uint32_t health);
    };
}
