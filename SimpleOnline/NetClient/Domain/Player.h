#pragma once
#include <cstdint>


namespace dungeon_client::domain
{
    class player
    {
    public:
        uint32_t id;
        uint32_t health;
    };
}
