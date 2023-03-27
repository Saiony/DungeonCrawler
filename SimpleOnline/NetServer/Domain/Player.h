#pragma once
#include <cstdint>
#include <string>

using namespace std;

namespace dungeon_common::domain
{
    class player
    {
    public:
        uint32_t private_id;
        uint32_t health;
        std::string name;
        
        void do_something();
        player(uint32_t id);
    };
}
