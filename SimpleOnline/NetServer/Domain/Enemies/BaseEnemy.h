#pragma once
#include <iostream>
#include <string>
#include "NetClient/Domain/encounter.h"
#include "NetServer/Domain/base_creature.h"

namespace dungeon_server::domain
{
    class encounter;
    
    class base_enemy : public base_creature
    {
    public:
        base_enemy(const std::string& name, const uint16_t health, const uint16_t damage);
        
        virtual void execute_turn(const std::shared_ptr<encounter>& encounter_ptr)
        {
            std::cout << "base execute turn" << std::endl;
        }
    };
}
