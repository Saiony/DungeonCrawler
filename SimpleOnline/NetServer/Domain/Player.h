#pragma once
#include <string>
#include "base_creature.h"

namespace dungeon_server::domain
{
    class player final : public base_creature
    {
    public:
        std::string private_id;
        
        void do_something() const;
        player(std::string client_id, std::string new_name, uint16_t new_health);
    };
}
