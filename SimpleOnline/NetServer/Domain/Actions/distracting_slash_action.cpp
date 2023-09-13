#include "distracting_slash_action.h"

dungeon_server::domain::action::distracting_slash_action::distracting_slash_action(const dungeon_common::model::action_types& action_type,
                                                                                   const std::string& new_action_owner_id, const std::string& target_id):
    base_action(action_type, new_action_owner_id),
    target_id_(target_id)
{
}

dungeon_server::domain::action::distracting_slash_action::~distracting_slash_action()
{
}

std::string dungeon_server::domain::action::distracting_slash_action::get_name()
{
    return "distracting slash";
}

std::uint8_t dungeon_server::domain::action::distracting_slash_action::get_targets_count()
{
    return 1;
}

dungeon_server::enums::offensive_stats_type dungeon_server::domain::action::distracting_slash_action::get_offensive_stat_type()
{
    return enums::offensive_stats_type::attack_damage;
}

float_t dungeon_server::domain::action::distracting_slash_action::get_damage_variance()
{
    return 0.2f;
}

float_t dungeon_server::domain::action::distracting_slash_action::get_offensive_stat_multiplier()
{
    return 1;
}

void dungeon_server::domain::action::distracting_slash_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    action_log += action_owner->name + " used " + get_name() + " on " + target->name;

    const auto damage = calculate_final_attack(encounter_ptr);
    target->take_damage(damage, action_log, encounter_ptr, action_owner_id);
    action_owner->on_attack(encounter_ptr, target_id_, action_log);

    //create opportunity
    const auto new_attacker_it = std::ranges::find_if(encounter_ptr->enemies, [&](auto enemy)
    {
        return enemy->public_id != action_owner_id;
    });

    if (new_attacker_it != std::end(encounter_ptr->enemies))
    {
        const auto new_attacker = *new_attacker_it;
        action_log += " and created an opportunity for " + new_attacker->name + "\n";
        new_attacker->execute_turn(encounter_ptr, action_log);
    }
}
