#include "celestial_weakening_action.h"

dungeon_server::domain::action::celestial_weakening_action::celestial_weakening_action(const dungeon_common::model::action_types& action_type,
                                                                                       const std::string& new_action_owner_id)
    : base_action(action_type, new_action_owner_id)
{
}

dungeon_server::domain::action::celestial_weakening_action::~celestial_weakening_action() = default;

std::string dungeon_server::domain::action::celestial_weakening_action::get_name()
{
    return "celestial weakening";
}

dungeon_server::enums::offensive_stats_type dungeon_server::domain::action::celestial_weakening_action::get_offensive_stat_type()
{
    return enums::offensive_stats_type::ability_power;
}

std::uint8_t dungeon_server::domain::action::celestial_weakening_action::get_targets_count()
{
    return 1;
}

float_t dungeon_server::domain::action::celestial_weakening_action::get_damage_variance()
{
    return 0.2f;
}

float_t dungeon_server::domain::action::celestial_weakening_action::get_offensive_stat_multiplier()
{
    return 0.5f;
}

void dungeon_server::domain::action::celestial_weakening_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    
}
