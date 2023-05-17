#include "heal_action.h"

domain::action::heal_action::~heal_action()
{
}

void domain::action::heal_action::use()
{
    std::cout << "[HEAL]";
}
