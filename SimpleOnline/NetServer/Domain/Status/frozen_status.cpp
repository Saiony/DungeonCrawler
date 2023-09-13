#include "frozen_status.h"

#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::frozen_status::~frozen_status() = default;

dungeon_server::domain::frozen_status::frozen_status(const std::string& creature_id, const std::shared_ptr<base_creature>& creature)
    : base_creature_status(creature_id, 1)
{
    creature->change_elemental_property(dungeon_common::enums::elemental_property_type::ice);
}

dungeon_common::enums::creature_status_type dungeon_server::domain::frozen_status::get_type()
{
    return dungeon_common::enums::creature_status_type::frozen;
}

void dungeon_server::domain::frozen_status::on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });

    action_log += "\n" + this_creature->name + " loses its turn due to freezing";
}

void dungeon_server::domain::frozen_status::on_end_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    quantity--;

    const auto this_creature = std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });

    if (quantity <= 0)
    {
        end_status(encounter);
        action_log += "\n" + (*this_creature)->name + " is no longer frozen";
    }
}

void dungeon_server::domain::frozen_status::on_overriding_status_added(std::shared_ptr<base_creature_status> status)
{
}

void dungeon_server::domain::frozen_status::on_attacked(const std::shared_ptr<encounter>& encounter, std::string& action_log,
                                                        const std::string& attacker_id, const uint16_t damage,
                                                        const dungeon_common::enums::elemental_property_type elemental_property)
{
    if (quantity <= 0)
        return;

    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });

    const auto ice_shatter_dmg = damage / 2;
    action_log += "\nThe ice shatters and " + this_creature->name + " takes additional damage";
    end_status(encounter);
    
    this_creature->take_damage(ice_shatter_dmg, action_log, encounter, nullptr, elemental_property);    
}

void dungeon_server::domain::frozen_status::end_status(const std::shared_ptr<encounter>& encounter)
{
    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });

    this_creature->set_original_elemental_property();
    on_end_action_(std::make_shared<frozen_status>(*this));
}