#include "sword_slash_action.h"

#include <iostream>

domain::action::sword_slash_action::~sword_slash_action() = default;

void domain::action::sword_slash_action::use()
{
    std::cout << "[SWORD SLASH] on " <<target_id << std::endl;
}
