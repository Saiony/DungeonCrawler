#pragma once
#include <vector>
#include "Player.h"

namespace dungeon_client::domain
{
    class enemy
    {
    private:
        std::string name_;
        uint16_t health_;
    public:
        enemy(const char* name, uint16_t health);
    };
    
    class encounter
    {
    private:
        std::vector<enemy> enemies_;
        std::vector<player> players_;
    public:
        encounter(std::vector<enemy> enemies, std::vector<player> players);
    };
}
