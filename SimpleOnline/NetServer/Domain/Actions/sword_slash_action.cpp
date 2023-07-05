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
    const auto action_owner = get_creature(encounter_ptr, action_owner_id);
    const auto target = get_creature(encounter_ptr, target_id);    
    const auto dmg_taken = target->take_damage(action_owner->attack_damage);

    //log
    std::string log = action_owner->name + " used " + get_name() +" on " +target->name +"\n" +target->name + " lost " +std::to_string(dmg_taken) +" hp";
    std::cout << "[SWORD SLASH] on " << target->name << std::endl;
    return log;
}

std::string dungeon_server::domain::action::sword_slash_action::get_name()
{
    return "sword slash";
}
