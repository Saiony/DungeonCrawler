#include "shield_bash.h"

#include <utility>

#include "NetServer/Domain/Status/stunned_status.h"
#include "NetServer/Utility/randomizer.h"

dungeon_server::domain::action::shield_bash::~shield_bash() = default;

dungeon_server::domain::action::shield_bash::shield_bash(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id, std::string target_id)
                                                        : base_action(action_type, std::move(new_action_owner_id)),
                                                        target_id_(std::move(target_id))
{
}

std::string dungeon_server::domain::action::shield_bash::get_name()
{
    return "shield bash";
}

std::uint8_t dungeon_server::domain::action::shield_bash::get_targets_count()
{
    return 1;
}

dungeon_server::enums::offensive_stats_type dungeon_server::domain::action::shield_bash::get_offensive_stat_type()
{
    return enums::offensive_stats_type::attack_damage;
}

float_t dungeon_server::domain::action::shield_bash::get_damage_variance()
{
    return 0.2f;
}

float_t dungeon_server::domain::action::shield_bash::get_offensive_stat_multiplier()
{
    return 0.5f;
}

void dungeon_server::domain::action::shield_bash::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    action_log += action_owner->name + " used " + get_name() +" on " +target->name;

    const auto damage = calculate_final_attack(encounter_ptr);
    target->take_damage(damage, action_log, encounter_ptr);

    const auto stun_chance = static_cast<uint16_t>(utility::randomizer::randomize(0, 100));
    if(stun_chance > 50)
    {
        target->add_status(std::make_shared<stunned_status>(target->public_id));
        action_log += "\n" + target->name + " is stunned";
    }
    
    action_owner->on_attack(encounter_ptr, target_id_, action_log);    
}
