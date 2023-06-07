#include "heal_action.h"

dungeon_server::domain::action::heal_action::~heal_action()
{
}

void dungeon_server::domain::action::heal_action::use()
{
    std::cout << "[HEAL]";
}
