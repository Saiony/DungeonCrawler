﻿#include "base_action.h"
#include <utility>
#include <random>

using namespace dungeon_server::domain;

action::base_action::~base_action() = default;

action::base_action::base_action(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id)
                                 : id(action_type), action_owner_id(std::move(new_action_owner_id))
{
}

std::shared_ptr<base_creature> action::base_action::get_creature(const std::shared_ptr<encounter>& encounter_ptr, const std::string& creature_id)
{    
    auto action_owner = *std::ranges::find_if(encounter_ptr->creatures, [this, &creature_id](auto enemy)
    {
       return enemy->public_id == creature_id;
    });

    return action_owner;
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
