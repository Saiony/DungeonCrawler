#include "base_action.h"
#include <utility>
#include <random>

using namespace dungeon_server::domain;

action::base_action::~base_action() = default;

action::base_action::base_action(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id)
    : id(action_type), action_owner_id(std::move(new_action_owner_id))
{
}

float_t action::base_action::randomize_damage(const float_t damage, const float_t damage_variance) const
{
    std::random_device dev;
    std::mt19937 rng(dev());

    const float_t min = damage * (1 - damage_variance);
    const float_t max = damage * (1 + damage_variance);
    std::uniform_real_distribution<float_t> dist6(min, max);

    const auto randomized_value = dist6(rng);
    std::cout << "[RANDOMIZED]: " << randomized_value << std::endl;

    return round(randomized_value);
}

uint16_t action::base_action::calculate_final_attack(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    float_t damage = 0;

    if (get_offensive_stat_type() == enums::offensive_stats_type::attack_damage)
        damage = static_cast<float_t>(action_owner->attack_damage);
    else if (get_offensive_stat_type() == enums::offensive_stats_type::ability_power)
        damage = static_cast<float_t>(action_owner->ability_power);

    damage *= get_offensive_stat_multiplier();
    damage = randomize_damage(damage, get_damage_variance());
    damage *= action_owner->get_attack_multipliers();

    return static_cast<uint16_t>(damage);
}
