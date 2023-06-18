#include "sword_slash_action.h"

#include <iostream>
#include <utility>

dungeon_server::domain::action::sword_slash_action::~sword_slash_action() = default;

dungeon_server::domain::action::sword_slash_action::sword_slash_action(const dungeon_common::model::action_types& action_type,
                                                        std::string new_action_owner_id, std::string target_id)
                                                        : base_action(action_type, std::move(new_action_owner_id)), target_id(std::move(target_id))
{
}

std::string dungeon_server::domain::action::sword_slash_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto target_it = std::ranges::find_if(encounter_ptr->creatures, [this](auto enemy)
    {
        return enemy->public_id == target_id;
    });

    const auto target = *target_it;
    std::cout << "[SWORD SLASH] on " << target->name << std::endl;
    const auto dmg_taken = target->take_damage(2);

    //log
    const auto action_owner = *std::ranges::find_if(encounter_ptr->creatures, [this](auto enemy)
    {
       return enemy->public_id == action_owner_id;
    });
    std::string log = action_owner->name + " used " + get_name() +" on " +target->name +"\n" +target->name + " lost " +std::to_string(dmg_taken) +" hp";

    return log;
}

std::string dungeon_server::domain::action::sword_slash_action::get_name()
{
    return "sword slash";
}
