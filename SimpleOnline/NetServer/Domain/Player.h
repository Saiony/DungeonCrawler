#pragma once
#include <cstdint>

namespace dungeon_common::domain
{
    class player
    {
    public:
        uint32_t private_id;
        uint32_t health;
        void do_something();
        player(uint32_t);
    };
}
