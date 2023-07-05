#include "heal_action.h"

dungeon_server::domain::action::heal_action::~heal_action() = default;

dungeon_server::domain::action::heal_action::heal_action(const dungeon_common::model::action_types& action_type,
                                                         const std::string& new_action_owner_id, std::string target_id)
                                                        : base_action(action_type, new_action_owner_id), target_id(std::move(target_id))
{
}


std::string dungeon_server::domain::action::heal_action::get_name()
{
    return "Heal";
}

std::string dungeon_server::domain::action::heal_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto action_owner = get_creature(encounter_ptr, action_owner_id);
    const auto target = get_creature(encounter_ptr, target_id);
    const auto hp_healed = target->heal(action_owner->ability_power);

    //log
    std::string log = action_owner->name + " used " + get_name() +" on " +target->name +"\n" +target->name + " healed " +std::to_string(hp_healed) +" hp";
    std::cout << "[HEAL] on " << target->name << std::endl;
    return log;
}
