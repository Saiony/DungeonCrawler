#include "silk_prison_action.h"

#include "NetServer/Domain/Status/stuck_in_spiders_web_status.h"

dungeon_server::domain::action::silk_prison_action::~silk_prison_action() = default;

dungeon_server::domain::action::silk_prison_action::silk_prison_action(const dungeon_common::model::action_types& action_type,
                                                                       std::string new_action_owner_id,
                                                                       std::string target_id)
    : base_action(action_type, std::move(new_action_owner_id)),
      target_id_(std::move(target_id))
{
}

std::string dungeon_server::domain::action::silk_prison_action::get_name()
{
    return "silk prison";
}

void dungeon_server::domain::action::silk_prison_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    action_log += action_owner->name + " used " + get_name() + " on " + target->name;

    const auto status = target->add_status(std::make_shared<stuck_in_spiders_web_status>(target->public_id));
    action_log += "\n" + target->name + " is entangled in a spider's web...";

    action_owner->on_attack(encounter_ptr, target_id_, action_log);
}
