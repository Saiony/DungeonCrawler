#include "Wolf.h"
#include <iostream>

dungeon_server::domain::enemy::wolf::wolf(const std::string& name, const uint16_t health, const uint16_t damage) : base_enemy(name, health, damage)
{
}

void dungeon_server::domain::enemy::wolf::execute_turn()
{
    std::cout << "BITE BITE BITE!! - Atk:" << damage_ << std::endl;
}
