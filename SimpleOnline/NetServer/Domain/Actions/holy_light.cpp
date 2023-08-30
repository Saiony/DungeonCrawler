﻿#include "holy_light.h"

#include <iostream>
#include <utility>

dungeon_server::domain::action::holy_light::~holy_light() = default;

dungeon_server::domain::action::holy_light::holy_light(const dungeon_common::model::action_types& action_type,
                                                        std::string new_action_owner_id, std::string target_id)
                                                        : base_action(action_type, std::move(new_action_owner_id)), target_id(std::move(target_id))
{
}

std::string dungeon_server::domain::action::holy_light::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id);
    std::string log = action_owner->name + " used " + get_name() + " on " +target->name;

    const auto damage = static_cast<uint16_t>(randomize_damage(static_cast<float_t>(action_owner->ability_power) * dmg_multiplier_, variance_));
    target->take_damage(damage, log);
    action_owner->on_attack(encounter_ptr, target_id, log);
    
    return log;
}

std::string dungeon_server::domain::action::holy_light::get_name()
{
    return "holy light";
}
