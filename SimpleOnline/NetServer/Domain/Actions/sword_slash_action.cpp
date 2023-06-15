#include "sword_slash_action.h"

#include <iostream>

dungeon_server::domain::action::sword_slash_action::~sword_slash_action() = default;

dungeon_server::domain::action::sword_slash_action::sword_slash_action(const dungeon_common::model::action_types& action_type, std::string new_target_id)
                                                                        : base_action(action_type), target_id(std::move(new_target_id))
{
}

void dungeon_server::domain::action::sword_slash_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto target_it = std::ranges::find_if(encounter_ptr->creatures, [this](auto enemy)
    {
        return enemy->public_id == target_id;
    });

    const auto target = *target_it;
    std::cout << "[SWORD SLASH] on " << target->name << std::endl;
    target->take_damage(2);    
}
