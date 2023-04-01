#pragma once
#include <cstdint>
#include <string>

namespace dungeon_common::model
{
    class player_model
    {
    public:
        uint32_t id_{};
        char name_[40]{};
        uint32_t health_{};
        
        player_model();
        player_model(uint32_t id, std::string name, uint32_t health);
    };
}
