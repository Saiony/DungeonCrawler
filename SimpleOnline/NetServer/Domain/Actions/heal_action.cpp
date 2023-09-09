#include "heal_action.h"

dungeon_server::domain::action::heal_action::~heal_action() = default;

dungeon_server::domain::action::heal_action::heal_action(const dungeon_common::model::action_types& action_type,
                                                         const std::string& new_action_owner_id, std::string target_id)
    : base_action(action_type, new_action_owner_id), target_id(std::move(target_id))
{
}


std::string dungeon_server::domain::action::heal_action::get_name()
{
    return "heal";
}

void dungeon_server::domain::action::heal_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id);
    const auto randomized_value = static_cast<uint16_t>(randomize_damage(action_owner->ability_power, variance_));
    const auto hp_healed = target->heal(randomized_value);

    action_log += (action_owner->name + " used " + get_name() + " on " + target->name + "\n" + target->name + " healed " + std::to_string(hp_healed) + " hp");
}
