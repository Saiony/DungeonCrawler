#include "stunned_status.h"
#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::stunned_status::stunned_status(const std::string& creature_id)
    : base_creature_status(creature_id, 1)
{
}

dungeon_common::enums::creature_status_type dungeon_server::domain::stunned_status::get_type()
{
    return dungeon_common::enums::creature_status_type::stun;
}

void dungeon_server::domain::stunned_status::on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    const auto this_creature = std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });
    action_log += "\n" + (*this_creature)->name + " is stunned";
}

void dungeon_server::domain::stunned_status::on_end_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    quantity--;
}

void dungeon_server::domain::stunned_status::on_overriding_status_added(std::shared_ptr<base_creature_status> status)
{
}
