#include "poisoned_status.h"

#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::poisoned_status::poisoned_status(const std::string& creature_id): base_creature_status(creature_id, 1)
{
}

dungeon_common::enums::creature_status_type dungeon_server::domain::poisoned_status::get_type()
{
    return dungeon_common::enums::creature_status_type::poisoned;
}

void dungeon_server::domain::poisoned_status::on_overriding_status_added(std::shared_ptr<base_creature_status> status)
{
    damage_ += std::static_pointer_cast<poisoned_status>(status)->damage_;
    quantity++;
}


void dungeon_server::domain::poisoned_status::on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });

    this_creature->take_damage(damage_, action_log, encounter, "", dungeon_common::enums::elemental_property_type::poison);
    const auto log = " due to poison...";
    action_log += log;
    std::cout << log;

    quantity--;

    if (quantity > 0)
        return;

    end_status_(std::make_shared<poisoned_status>(*this));
    action_log += "\n" + this_creature->name + " is no longer poisoned";
}