#include "sword_slash_action.h"

#include <iostream>
#include <utility>

dungeon_server::domain::action::sword_slash_action::~sword_slash_action() = default;

dungeon_server::domain::action::sword_slash_action::sword_slash_action(const dungeon_common::model::action_types& action_type,
                                                        std::string new_action_owner_id, std::string target_id)
                                                        : base_action(action_type, std::move(new_action_owner_id)), target_id(std::move(target_id))
{
}

void dungeon_server::domain::action::sword_slash_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id);
    action_log += action_owner->name + " used " + get_name() + " on " +target->name;

    const auto damage = static_cast<uint16_t>(randomize_damage(action_owner->attack_damage, variance_));
    target->take_damage(damage, action_log);
    action_owner->on_attack(encounter_ptr, target_id, action_log);
}

std::string dungeon_server::domain::action::sword_slash_action::get_name()
{
    return "sword slash";
}
