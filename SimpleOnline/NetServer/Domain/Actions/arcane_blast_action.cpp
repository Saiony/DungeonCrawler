#include "arcane_blast_action.h"

dungeon_server::domain::action::arcane_blast_action::arcane_blast_action(const dungeon_common::model::action_types& action_type,
                                                                         const std::string& new_action_owner_id,
                                                                         std::string target_id)
    : base_action(action_type, new_action_owner_id),
      target_id_(std::move(target_id))
{
}

dungeon_server::domain::action::arcane_blast_action::~arcane_blast_action() = default;

std::string dungeon_server::domain::action::arcane_blast_action::get_name()
{
    return "arcane blast";
}

std::uint8_t dungeon_server::domain::action::arcane_blast_action::get_targets_count()
{
    return 1;
}

dungeon_server::enums::offensive_stats_type dungeon_server::domain::action::arcane_blast_action::get_offensive_stat_type()
{
    return enums::offensive_stats_type::ability_power;
}

float_t dungeon_server::domain::action::arcane_blast_action::get_damage_variance()
{
    return 0.2f;
}

float_t dungeon_server::domain::action::arcane_blast_action::get_offensive_stat_multiplier()
{
    return 1.0f;
}

void dungeon_server::domain::action::arcane_blast_action::use(const std::shared_ptr<encounter>& encounter_ptr, action_log& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    action_log.add_log(action_owner->name + " used " + get_name() + " on " + target->name);

    const auto damage = calculate_final_attack(encounter_ptr);
    target->take_damage(damage, action_log, encounter_ptr, action_owner_id, dungeon_common::enums::elemental_property_type::arcane);
    action_owner->on_attack(encounter_ptr, target_id_, action_log);
}
