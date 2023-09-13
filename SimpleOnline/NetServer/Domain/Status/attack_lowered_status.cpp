#include "attack_lowered_status.h"

#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::attack_lowered_status::attack_lowered_status(const std::string& creature_id, const std::shared_ptr<encounter>& encounter_ptr,
                                                                     const uint8_t duration)
    : base_creature_status(creature_id, duration)
{
    const auto this_creature = encounter_ptr->get_creature(creature_id);
    this_creature->modify_offensive_stat(enums::offensive_stats_type::ability_power, -debuff_value_);
    this_creature->modify_offensive_stat(enums::offensive_stats_type::attack_damage, -debuff_value_);
}

dungeon_common::enums::creature_status_type dungeon_server::domain::attack_lowered_status::get_type()
{
    return dungeon_common::enums::creature_status_type::attack_lowered;
}

void dungeon_server::domain::attack_lowered_status::on_overriding_status_added(const std::shared_ptr<base_creature_status> status)
{
    quantity = status->quantity;
}

void dungeon_server::domain::attack_lowered_status::on_end_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    quantity--;

    if (quantity <= 0)
    {
        const auto this_creature = encounter->get_creature(creature_id_);
        this_creature->modify_offensive_stat(enums::offensive_stats_type::ability_power, debuff_value_);
        this_creature->modify_offensive_stat(enums::offensive_stats_type::attack_damage, debuff_value_);

        action_log += "\n" + this_creature->name + " 's attack is no longer lowered";
        on_end_action_(std::make_shared<attack_lowered_status>(*this));
    }
}
