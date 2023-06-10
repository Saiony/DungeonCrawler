#pragma once
#include <cstdint>
#include <string>

namespace dungeon_common::model
{
    class player_model
    {
    public:
        char id[38]{};
        char name[40]{};
        uint32_t health{};
        
        player_model();
        player_model(const std::string& new_id, const std::string& new_name, uint32_t health);
    };
}
