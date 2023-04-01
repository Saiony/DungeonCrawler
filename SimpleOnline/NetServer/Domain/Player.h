#pragma once
#include <cstdint>
#include <string>

using namespace std;

namespace dungeon_common::domain
{
    class player
    {
    public:
        uint16_t private_id;
        uint16_t health;
        std::string name;
        
        void do_something();
        player(uint16_t id, std::string name, uint16_t health);
    };
}
