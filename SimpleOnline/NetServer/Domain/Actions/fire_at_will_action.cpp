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

std::string dungeon_server::domain::action::fire_at_will_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const uint8_t shot_count = 3;
    std::string log;
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);

    log += action_owner->name + " used " + get_name();
    for (int i = 0; i < shot_count; ++i)
    {
        log += "\nAn arrow takes flight...";
        const int random_index = utility::randomizer::randomize(0, static_cast<int>(std::size(encounter_ptr->enemies) - 1));
        const auto target = encounter_ptr->enemies[random_index];

        const auto damage = static_cast<uint16_t>(randomize_damage(static_cast<float_t>(action_owner->attack_damage) * dmg_multiplier_, variance_));
        target->take_damage(damage, log);
        action_owner->on_attack(encounter_ptr, target->public_id, log);
    }
    
    return log;
}
