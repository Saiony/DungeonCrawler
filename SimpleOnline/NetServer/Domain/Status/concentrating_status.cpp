#include "concentrating_status.h"

dungeon_common::enums::creature_status_type dungeon_server::domain::concentrating_status::get_type()
{
    return dungeon_common::enums::creature_status_type::concentrating;
}

void dungeon_server::domain::concentrating_status::on_after_attack(const std::shared_ptr<encounter>& encounter,
                                                             const std::string& attacked_creature_id,
                                                             std::string& action_log)
{
    quantity = 0;
}

int16_t dungeon_server::domain::concentrating_status::get_attack_multiplier()
{
    return quantity;
}
