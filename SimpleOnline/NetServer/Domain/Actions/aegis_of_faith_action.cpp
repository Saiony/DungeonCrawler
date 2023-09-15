#include "aegis_of_faith_action.h"

#include "NetServer/Domain/Status/invulnerable_status.h"

dungeon_server::domain::action::aegis_of_faith_action::aegis_of_faith_action(const dungeon_common::model::action_types& action_type,
                                                                             const std::string& new_action_owner_id, const std::string& target_id)
    : base_action(action_type, new_action_owner_id), target_id_(std::move(target_id))
{
}

dungeon_server::domain::action::aegis_of_faith_action::~aegis_of_faith_action() = default;

std::string dungeon_server::domain::action::aegis_of_faith_action::get_name()
{
    return "aegis of faith";
}

std::uint8_t dungeon_server::domain::action::aegis_of_faith_action::get_targets_count()
{
    return 1;
}

void dungeon_server::domain::action::aegis_of_faith_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    action_log += action_owner->name + " used " + get_name() + " on " + target->name;

    target->add_status(std::make_shared<invulnerable_status>(target_id_));

    action_log += "\n" + target->name + " is invulnerable";
}
