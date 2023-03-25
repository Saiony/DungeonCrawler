#pragma once
#include <cstdint>

namespace dungeon
{
    namespace model
    {
        class player_model
        {
        public:
            uint16_t id = -1;
            char name[40]{};
            uint16_t health = -1;

            player_model(uint16_t id, char name[],uint16_t health);
            player_model();
        };
    }
}
