#include "celestial_weakening_action.h"

#include "NetServer/Domain/Status/attack_lowered_status.h"

dungeon_server::domain::action::celestial_weakening_action::celestial_weakening_action(const dungeon_common::model::action_types& action_type,
                                                                                       const std::string& new_action_owner_id,
                                                                                       std::string target_id)
    : base_action(action_type, new_action_owner_id), target_id_(std::move(target_id))
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
    return 0.5;
}

void dungeon_server::domain::action::celestial_weakening_action::use(const std::shared_ptr<encounter>& encounter, action_log& action_log)
{
    const auto action_owner = encounter->get_creature(action_owner_id);
    const auto target = encounter->get_creature(target_id_);
    action_log.add_log(action_owner->name + " used " + get_name() + " on " + target->name);

    const auto damage = calculate_final_attack(encounter);
    constexpr auto duration = 2;
    target->take_damage(damage, action_log, encounter, action_owner_id, dungeon_common::enums::elemental_property_type::holy);
    target->add_status(std::make_shared<attack_lowered_status>(target->public_id, encounter, duration));

    action_log.add_log(target->name + " 's attack is lowered for " + std::to_string(duration) + " turns");
    action_owner->on_attack(encounter, target_id_, action_log);
}
