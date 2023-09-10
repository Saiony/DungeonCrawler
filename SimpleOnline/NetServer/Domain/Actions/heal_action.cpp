#include "heal_action.h"

dungeon_server::domain::action::heal_action::~heal_action() = default;

dungeon_server::domain::action::heal_action::heal_action(const dungeon_common::model::action_types& action_type,
                                                         const std::string& new_action_owner_id, std::string target_id)
    : base_action(action_type, new_action_owner_id), target_id_(std::move(target_id))
{
}


std::string dungeon_server::domain::action::heal_action::get_name()
{
    return "heal";
}

std::uint8_t dungeon_server::domain::action::heal_action::get_targets_count()
{
    return 1;
}

dungeon_server::enums::offensive_stats_type dungeon_server::domain::action::heal_action::get_offensive_stat_type()
{
    return enums::offensive_stats_type::ability_power;
}

float_t dungeon_server::domain::action::heal_action::get_damage_variance()
{
    return 0.2f;
}

float_t dungeon_server::domain::action::heal_action::get_offensive_stat_multiplier()
{
    return 1;
}

void dungeon_server::domain::action::heal_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    const auto value = calculate_final_attack(encounter_ptr);
    const auto hp_healed = target->heal(value);

    action_log += (action_owner->name + " used " + get_name() + " on " + target->name + "\n" + target->name + " healed " + std::to_string(hp_healed) + " hp");
}
