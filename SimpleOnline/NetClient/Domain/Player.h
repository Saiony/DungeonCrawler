#pragma once
#include <cstdint>
#include <string>


namespace dungeon_client::domain
{
    class player
    {
    public:
        std::string id{};
        std::string name{};
        uint32_t health{};

        player();
        player(std::string id, std::string name, uint32_t health);
    };
}
