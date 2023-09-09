#include "shield_bash.h"

#include <utility>

#include "NetServer/Domain/Status/stunned_status.h"

dungeon_server::domain::action::shield_bash::shield_bash(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id, std::string target_id)
                                                        : base_action(action_type, std::move(new_action_owner_id)),
                                                        target_id(std::move(target_id))
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

void dungeon_server::domain::action::shield_bash::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id);
    const auto base_dmg = static_cast<uint16_t>(static_cast<float_t>(action_owner->attack_damage) * dmg_multiplier_);
    const auto final_dmg = static_cast<uint16_t>(randomize_damage(base_dmg, variance_));
    
    action_log += action_owner->name + " used " + get_name() +" on " +target->name;
    target->take_damage(final_dmg, action_log);

    const auto stun_chance = static_cast<uint16_t>(randomize_damage(50, 0.5f));
    if(stun_chance > 50)
    {
        target->add_status(std::make_shared<stunned_status>(target->public_id));
        action_log += "\n" + target->name + " is stunned";
    }
    
    action_owner->on_attack(encounter_ptr, target_id, action_log);    
}
