#include "concentrating_status.h"

dungeon_server::domain::concentrating_status::concentrating_status(const std::string& creature_id)
    : base_creature_status(creature_id, 1)
{
}

dungeon_common::enums::creature_status_type dungeon_server::domain::concentrating_status::get_type()
{
    return dungeon_common::enums::creature_status_type::concentrating;
}

void dungeon_server::domain::concentrating_status::on_after_attack(const std::shared_ptr<encounter>& encounter,
                                                                   const std::string& attacked_creature_id,
                                                                   dungeon_server::domain::action_log& action_log)
{
    quantity = 0;
}

int16_t dungeon_server::domain::concentrating_status::get_attack_multiplier()
{
    return quantity + 1;
}

void dungeon_server::domain::concentrating_status::on_overriding_status_added(const std::shared_ptr<base_creature_status> status)
{
    quantity += status->quantity;
}
