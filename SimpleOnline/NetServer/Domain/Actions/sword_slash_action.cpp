#include "sword_slash_action.h"

#include <iostream>

domain::action::sword_slash_action::~sword_slash_action() = default;

void domain::action::sword_slash_action::use()
{
    std::cout << "[SWORD SLASH] on " <<target_id << std::endl;
    const auto target = std::ranges::find_if(encounter->enemies, [this](auto& enemy)
    {
        return enemy.get_id() == target_id;
    });

    target->take_damage(2);    
}
