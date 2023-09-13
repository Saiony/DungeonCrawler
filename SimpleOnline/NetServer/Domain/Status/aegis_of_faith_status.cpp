#include "aegis_of_faith_status.h"

dungeon_server::domain::aegis_of_faith_status::aegis_of_faith_status(const std::string& creature_id, uint8_t quantity)
    : base_creature_status(creature_id, quantity)
{
}

dungeon_server::domain::aegis_of_faith_status::~aegis_of_faith_status() = default;
    
dungeon_common::enums::creature_status_type dungeon_server::domain::aegis_of_faith_status::get_type()
{
    return dungeon_common::enums::creature_status_type::aegis_of_faith;
}

void dungeon_server::domain::aegis_of_faith_status::on_overriding_status_added(std::shared_ptr<base_creature_status> status)
{    
}