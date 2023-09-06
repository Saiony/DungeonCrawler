#include "arrow_shot_action.h"

dungeon_server::domain::action::arrow_shot_action::arrow_shot_action(const dungeon_common::model::action_types& action_type,
                                                                     const std::string& new_action_owner_id, std::string target_id)
                                                       : base_action(action_type, new_action_owner_id), target_id_(std::move(target_id))
{
}

dungeon_server::domain::action::arrow_shot_action::~arrow_shot_action()
{
}

std::string dungeon_server::domain::action::arrow_shot_action::get_name()
{
    return "arrow shot";
}

std::uint8_t dungeon_server::domain::action::arrow_shot_action::get_targets_count()
{
    return 1;
}

std::string dungeon_server::domain::action::arrow_shot_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    const auto damage = static_cast<uint16_t>(randomize_damage(action_owner->attack_damage, variance_));
    
    std::string log = action_owner->name + " used " + get_name() +" on " +target->name;
    target->take_damage(damage, log);
    action_owner->on_attack(encounter_ptr, target_id_, log);
    
    return log;
}

