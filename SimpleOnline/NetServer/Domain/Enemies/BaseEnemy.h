#pragma once
#include <iostream>
#include <string>
#include "NetServer/Domain/base_creature.h"

namespace dungeon_server::domain
{
    class base_enemy : public base_creature
    {
    protected:
        std::string name_;
        uint16_t health_;
        uint16_t damage_;

    public:
        base_enemy(std::string name, const uint16_t health, const uint16_t damage);
        std::string get_name() const;
        uint16_t get_health() const;
        std::string get_id() const;
        void take_damage(int damage);
        virtual void execute_turn()
        {
            std::cout << "base execute turn" << std::endl;
        }
    };
}
