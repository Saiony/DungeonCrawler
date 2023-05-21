#pragma once
#include <string>

namespace dungeon_server::domain
{
    class player
    {
    public:
        uint16_t private_id;
        std::string public_id;
        uint16_t health;
        std::string name;
        
        void do_something() const;
        player(uint16_t client_id, std::string name, uint16_t health);
    };
}
