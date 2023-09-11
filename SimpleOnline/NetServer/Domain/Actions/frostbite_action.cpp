#include "frostbite_action.h"

#include "NetServer/Domain/Status/frozen_status.h"
#include "NetServer/Utility/randomizer.h"

dungeon_server::domain::action::frostbite_action::frostbite_action(const dungeon_common::model::action_types& action_type,
                                                                   const std::string& new_action_owner_id,
                                                                   std::string target_id)
                                                                   : base_action(action_type, new_action_owner_id),
                                                                   target_id_(std::move(target_id))
{
}

dungeon_server::domain::action::frostbite_action::~frostbite_action() = default;

std::string dungeon_server::domain::action::frostbite_action::get_name()
{
    return "frostbite";
}

std::uint8_t dungeon_server::domain::action::frostbite_action::get_targets_count()
{
    return 1;
}

dungeon_server::enums::offensive_stats_type dungeon_server::domain::action::frostbite_action::get_offensive_stat_type()
{
    return enums::offensive_stats_type::ability_power;
}

float_t dungeon_server::domain::action::frostbite_action::get_damage_variance()
{
    return 0.5f;
}

float_t dungeon_server::domain::action::frostbite_action::get_offensive_stat_multiplier()
{
    return 1.0f;
}

void dungeon_server::domain::action::frostbite_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    action_log += action_owner->name + " used " + get_name() + " on " + target->name;

    const auto damage = calculate_final_attack(encounter_ptr);
    target->take_damage(damage, action_log, encounter_ptr, dungeon_common::enums::elemental_property_type::ice);

    const auto percentage = static_cast<uint16_t>(utility::randomizer::randomize(0, 100));
    if(percentage <= freeze_chance_)
    {
        target->add_status(std::make_shared<frozen_status>(target->public_id, target));
        action_log += "\n" + target->name + " is frozen";
    }
    
    action_owner->on_attack(encounter_ptr, target_id_, action_log);
}
