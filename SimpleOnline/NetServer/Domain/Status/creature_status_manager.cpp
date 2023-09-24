#include "creature_status_manager.h"
#include <algorithm>

#include "NetServer/Domain/action_log.h"

std::shared_ptr<dungeon_server::domain::base_creature_status> dungeon_server::domain::creature_status_manager::add_status(
    const std::shared_ptr<base_creature_status>& status)
{
    if (!contains(status->get_type()))
    {
        statuses_[status->get_type()] = status;
        statuses_[status->get_type()]->add_on_end_listener([&](const std::shared_ptr<base_creature_status>& ended_status)
        {
            if(!statuses_.contains(ended_status->get_type()))
                return;

            statuses_.erase(ended_status->get_type());
        });
        
        return statuses_[status->get_type()];
    }

    auto updated_status = statuses_[status->get_type()];
    updated_status->on_overriding_status_added(status);
    return updated_status;
}

bool dungeon_server::domain::creature_status_manager::contains(const dungeon_common::enums::creature_status_type status_type) const
{
    return statuses_.contains(status_type);
}

uint16_t dungeon_server::domain::creature_status_manager::get_attack_multipliers()
{
    uint16_t multiplier = 1;
    std::ranges::for_each(statuses_, [&multiplier](auto status)
    {
        auto status_multiplier = status.second->get_attack_multiplier();
        if (status_multiplier == -1)
            return;

        multiplier *= status_multiplier;
    });

    return multiplier;
}

void dungeon_server::domain::creature_status_manager::on_begin_of_turn(std::shared_ptr<encounter> encounter, action_log& action_log)
{
    std::ranges::for_each(statuses_, [&action_log, &encounter](auto status)
    {
        status.second->on_begin_of_turn(encounter, action_log);
    });
}

void dungeon_server::domain::creature_status_manager::on_attack(std::shared_ptr<encounter> encounter,
                                                                const std::string& attacked_creature_id,
                                                                action_log& action_log)
{
    std::ranges::for_each(statuses_, [&action_log, &encounter, &attacked_creature_id](auto status)
    {
        status.second->on_after_attack(encounter, attacked_creature_id, action_log);
    });
}

void dungeon_server::domain::creature_status_manager::on_attacked(const std::shared_ptr<encounter>& encounter,
                                                                  action_log& action_log,
                                                                  const std::string& attacker_id,
                                                                  uint16_t damage,
                                                                  dungeon_common::enums::elemental_property_type elemental_property)
{
    std::ranges::for_each(statuses_, [&action_log, &elemental_property, &attacker_id, &damage, &encounter](auto status)
    {
        status.second->on_attacked(encounter, action_log, attacker_id, damage, elemental_property);
    });
}

void dungeon_server::domain::creature_status_manager::on_end_of_turn(std::shared_ptr<encounter> encounter, action_log& action_log)
{
    std::ranges::for_each(statuses_, [&action_log, &encounter](auto status)
    {
        status.second->on_end_of_turn(encounter, action_log);
    });

    std::erase_if(statuses_, [](auto status)
    {
        return status.second->quantity <= 0;
    });
}