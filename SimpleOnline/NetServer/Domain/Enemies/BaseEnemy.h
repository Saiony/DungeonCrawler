#pragma once
#include <string>

namespace dungeon_server::domain::enemy
{
    class base_enemy
    {
    protected:
        int id_;
        const char* name_;
        uint16_t health_;
        uint16_t damage_;

    public:
        base_enemy(const char* name, const uint16_t health, const uint16_t damage);
        virtual void execute_turn();
    };
}
