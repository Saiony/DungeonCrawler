#pragma once
#include <cstdint>
#include <string>

#include "base_creature.h"

namespace dungeon_client::domain
{
    class player : public base_creature
    {
    public:
        player();
        player(const std::string& id, const std::string& name, uint32_t health);
    };
}
