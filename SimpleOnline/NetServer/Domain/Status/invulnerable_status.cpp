#include "invulnerable_status.h"

#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::invulnerable_status::invulnerable_status(const std::string& creature_id)
    : base_creature_status(creature_id, 1)
{
}

dungeon_server::domain::invulnerable_status::~invulnerable_status() = default;


dungeon_common::enums::creature_status_type dungeon_server::domain::invulnerable_status::get_type()
{
    return dungeon_common::enums::creature_status_type::invulnerable;
}

void dungeon_server::domain::invulnerable_status::on_overriding_status_added(std::shared_ptr<base_creature_status> status)
{
}

void dungeon_server::domain::invulnerable_status::on_attacked(const std::shared_ptr<encounter>& encounter, std::string& action_log,
                                                              const std::string& attacker_id, uint16_t damage,
                                                              dungeon_common::enums::elemental_property_type elemental_property)
{
    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
        
    });
    
    action_log += "\n" + this_creature->name + " is invulnerable";
    quantity--;

    if (quantity > 0)
        return;
        
    end_status_(std::make_shared<invulnerable_status>(*this));
    action_log += "\n" + this_creature->name + " is no longer invulnerable";
}
