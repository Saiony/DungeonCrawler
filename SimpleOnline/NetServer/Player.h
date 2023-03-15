#pragma once
#include <cstdint>

namespace dungeon
{
    namespace server
    {
        class player
        {
        public:
            uint32_t id;
            void do_something();
            player(uint32_t);
        };
    }
}
