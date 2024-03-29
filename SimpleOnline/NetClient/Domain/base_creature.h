﻿#pragma once
#include <string>

namespace dungeon_client::domain
{
    class base_creature
    {
    public:
        std::string public_id;
        std::string name;
        uint16_t health{};
        uint16_t max_health{};
        
        base_creature() = default;

        base_creature(std::string id, std::string name, const uint16_t health, const uint16_t max_health) : public_id(std::move(id)), name(std::move(name)),
                      health(health), max_health(max_health)
        {
        }
    };
}
