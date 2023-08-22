#pragma once
#include <cstdint>
#include <string>

#include "base_creature.h"
#include "player_class.h"

namespace dungeon_client::domain
{
    class player : public base_creature
    {
    public:
        player_class my_class;   
        
        player();
        player(const std::string& id, const std::string& name, player_class player_class, uint16_t health, uint16_t max_health);
    };
}