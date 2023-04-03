#pragma once
#include <cstdint>
#include <string>


namespace dungeon_client::domain
{
    class player
    {
    public:
        uint32_t id;
        std::string name;
        uint32_t health;

        player();
        player(uint32_t id, std::string name, uint32_t health);
    };
}
