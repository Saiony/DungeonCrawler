#pragma once
#include <cstdint>
#include <string>

namespace dungeon_common::model
{
    class player_model
    {
    private:
        uint16_t id_{};
        char name_[40]{};
        uint16_t health_{};

    public:
        player_model();
        player_model(uint16_t id, std::string name, uint16_t health);
        uint16_t get_id();
    };
}
