#include "frostbite_action.h"

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
    
}
