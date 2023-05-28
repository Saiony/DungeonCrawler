#pragma once
#include <string>

namespace dungeon_server::domain
{
    class player
    {
    public:
        std::string private_id;
        std::string public_id;
        uint16_t health;
        std::string name;
        
        void do_something() const;
        player(const std::string& client_id, std::string name, uint16_t health);
    };
}
