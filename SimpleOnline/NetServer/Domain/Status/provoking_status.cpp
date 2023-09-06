#include "provoking_status.h"

#include "NetClient/Domain/Player.h"
#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::provoking_status::provoking_status(const std::string& creature_id, const std::shared_ptr<encounter>& encounter_ptr)
                                                           : base_creature_status(creature_id, 3)
{
    const auto player = encounter_ptr->get_player(creature_id);
    player->aggro += aggro_increase_;
}

dungeon_common::enums::creature_status_type dungeon_server::domain::provoking_status::get_type()
{
    return dungeon_common::enums::creature_status_type::provoking;
}


void dungeon_server::domain::provoking_status::on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    quantity--;

    if(quantity <= 0)
    {
        const auto player = encounter->get_player(creature_id_);
        player->aggro -= aggro_increase_;
        
        action_log += "\n" +player->name +"'s Provoke is no longer active";
    }
}