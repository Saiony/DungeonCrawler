#include "sword_slash_action.h"

#include <iostream>

dungeon_server::domain::action::sword_slash_action::~sword_slash_action() = default;

void dungeon_server::domain::action::sword_slash_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto target_it = std::ranges::find_if(encounter_ptr->enemies, [this](auto enemy)
    {
        std::cout << "caue --- comparing " << enemy->get_id() << " - " << target_id;
        return enemy->get_id() == target_id;
    });

    const auto target = *target_it;
    std::cout << "[SWORD SLASH] on " << target->get_name() << std::endl;
    target->take_damage(2);    
}
