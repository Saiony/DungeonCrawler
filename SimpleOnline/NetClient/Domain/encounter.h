﻿#pragma once
#include <vector>
#include "Player.h"

namespace dungeon_client::domain
{
    class enemy
    {
    private:
        std::string id_;
        std::string name_;
        uint16_t health_;
    public:
        enemy(const char* id, const char* name, uint16_t health);
        std::string get_name();
        std::string get_id();
        uint16_t get_health() const;
    };
    
    class encounter
    {
    public:
        std::vector<enemy> enemies;
        std::vector<player> players;
        
        encounter(std::vector<enemy> enemies, std::vector<player> players);
    };
}