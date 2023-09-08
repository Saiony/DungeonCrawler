#include "distracting_slash_action.h"

dungeon_server::domain::action::distracting_slash_action::distracting_slash_action(const dungeon_common::model::action_types& action_type,
                                                                                   const std::string& new_action_owner_id, const std::string& target_id):
    base_action(action_type, new_action_owner_id),
    target_id(target_id)
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

std::string dungeon_server::domain::action::distracting_slash_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id);
    const auto damage = static_cast<uint16_t>(randomize_damage(action_owner->attack_damage, variance_));

    std::string log = action_owner->name + " used " + get_name() + " on " + target->name;
    target->take_damage(damage, log);
    action_owner->on_attack(encounter_ptr, target_id, log);

    //create opportunity
    const auto new_attacker_it = std::ranges::find_if(encounter_ptr->enemies, [&](auto enemy)
    {
        return enemy->public_id != action_owner_id;
    });

    if (new_attacker_it != std::end(encounter_ptr->enemies))
    {
        const auto new_attacker = *new_attacker_it;
        log += " and created an opportunity for " + new_attacker->name + "\n";
        new_attacker->execute_turn(encounter_ptr, log);
    }

    return log;
}
