#pragma once
#include <string>
#include "base_creature.h"

namespace dungeon_server::domain
{
    class player : public base_creature
    {
    public:
        std::string private_id;
        uint16_t health;
        std::string name;
        
        void do_something() const;
        player(const std::string& client_id, std::string name, uint16_t health);
    };
}
