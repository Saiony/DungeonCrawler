﻿#include "eagle_petted_status.h"

#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::eagle_petted_status::eagle_petted_status(const std::string& creature_id)
    : base_creature_status(creature_id, 3)
{
}

dungeon_common::enums::creature_status_type dungeon_server::domain::eagle_petted_status::get_type()
{
    return dungeon_common::enums::creature_status_type::eagle_petted;
}

void dungeon_server::domain::eagle_petted_status::on_after_attack(const std::shared_ptr<encounter>& encounter, const std::string& attacked_creature_id,
                                                                  dungeon_server::domain::action_log& action_log)
{
    const auto attacked_creature = encounter->get_creature(attacked_creature_id);
    action_log.add_log("Eagle attacked " + attacked_creature->name);
   
    attacked_creature->take_damage(damage_, action_log, encounter);
}

void dungeon_server::domain::eagle_petted_status::on_end_of_turn(const std::shared_ptr<encounter>& encounter, dungeon_server::domain::action_log& action_log)
{
    quantity--;

    if (quantity <= 0)
        action_log.add_log("Eagle does not feel cared anymore");
}

void dungeon_server::domain::eagle_petted_status::on_overriding_status_added(std::shared_ptr<base_creature_status> status)
{
    quantity += status->quantity;
}
