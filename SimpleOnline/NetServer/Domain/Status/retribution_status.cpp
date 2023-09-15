#include "retribution_status.h"

#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::retribution_status::retribution_status(const std::string& creature_id)
    : base_creature_status(creature_id, 3)
{
}

dungeon_server::domain::retribution_status::~retribution_status() = default;

dungeon_common::enums::creature_status_type dungeon_server::domain::retribution_status::get_type()
{
    return dungeon_common::enums::creature_status_type::retribution;
}

void dungeon_server::domain::retribution_status::on_overriding_status_added(std::shared_ptr<base_creature_status> status)
{
    quantity = duration_;
}

void dungeon_server::domain::retribution_status::on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    quantity--;

    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });

    if (quantity <= 0)
    {
        end_status_(std::make_shared<retribution_status>(*this));
        action_log += "\n" + this_creature->name + "'s retribution is no longer active";
    }
}

void dungeon_server::domain::retribution_status::on_attacked(const std::shared_ptr<encounter>& encounter, std::string& action_log,
                                                             const std::string& attacker_id, const uint16_t damage,
                                                             const dungeon_common::enums::elemental_property_type elemental_property)
{
    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });

    const auto attacker = *std::ranges::find_if(encounter->creatures, [&attacker_id](auto creature)
    {
        return creature->public_id == attacker_id;
    });

    const auto retribution_dmg = static_cast<uint16_t>(static_cast<float_t>(this_creature->get_attack_damage()) * multiplier_);
    action_log += "\n" + this_creature->name + " counter attacks";
    attacker->take_damage(retribution_dmg, action_log, encounter, creature_id_, dungeon_common::enums::elemental_property_type::normal);
}
