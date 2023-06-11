#pragma once
#include <string>
#include "base_creature.h"

namespace dungeon_client::domain
{
    class enemy : public base_creature
    {
    public:
        enemy(const char* id, const char* name, uint16_t health);
    };
}
