#include "burning_status.h"

#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::burning_status::burning_status(const std::string& creature_id)
    : base_creature_status(creature_id, 2)
{
    damage_ = 3;
}

dungeon_common::enums::creature_status_type dungeon_server::domain::burning_status::get_type()
{
    return dungeon_common::enums::creature_status_type::burning;
}

void dungeon_server::domain::burning_status::on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });

    this_creature->take_damage(damage_, action_log, encounter, "", dungeon_common::enums::elemental_property_type::fire);
    const auto burn_log = " due to burning...";
    action_log += burn_log;
    std::cout << burn_log;

    if (quantity > 0)
        return;

    end_status_(std::make_shared<burning_status>(*this));
    action_log += "\n" + this_creature->name + " is no longer burning";
}

void dungeon_server::domain::burning_status::on_overriding_status_added(const std::shared_ptr<base_creature_status> status)
{
    damage_ += (std::static_pointer_cast<burning_status>(status)->damage_ / 2);
}
