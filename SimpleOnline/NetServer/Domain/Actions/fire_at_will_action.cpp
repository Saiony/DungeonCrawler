#include "fire_at_will_action.h"

#include <random>

#include "NetServer/Utility/randomizer.h"

dungeon_server::domain::action::fire_at_will_action::fire_at_will_action(const dungeon_common::model::action_types& action_type,
                                                                         std::string new_action_owner_id)
                                                                         : base_action(action_type, std::move(new_action_owner_id))
{
}

dungeon_server::domain::action::fire_at_will_action::~fire_at_will_action() = default;

std::string dungeon_server::domain::action::fire_at_will_action::get_name()
{
    return "fire at will";
}

dungeon_server::enums::offensive_stats_type dungeon_server::domain::action::fire_at_will_action::get_offensive_stat_type()
{
    return enums::offensive_stats_type::attack_damage;
}

float_t dungeon_server::domain::action::fire_at_will_action::get_damage_variance()
{
    return 0.3f;
}

float_t dungeon_server::domain::action::fire_at_will_action::get_offensive_stat_multiplier()
{
    return 0.5;
}

void dungeon_server::domain::action::fire_at_will_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const uint8_t shot_count = 3;
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);

    action_log += action_owner->name + " used " + get_name();
    for (int i = 0; i < shot_count; ++i)
    {
        action_log += "\nAn arrow takes flight...";
        const int random_index = utility::randomizer::randomize(0, static_cast<int>(std::size(encounter_ptr->enemies) - 1));
        const auto target = encounter_ptr->enemies[random_index];

        const auto damage = calculate_final_attack(encounter_ptr);
        target->take_damage(damage, action_log);
        action_owner->on_attack(encounter_ptr, target->public_id, action_log);
    }
}
