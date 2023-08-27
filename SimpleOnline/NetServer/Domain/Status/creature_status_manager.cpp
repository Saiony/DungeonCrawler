#include "creature_status_manager.h"
#include <algorithm>

void dungeon_server::domain::creature_status_manager::add_status(const std::shared_ptr<base_creature_status>& status)
{
    statuses_.push_back(status);
}

bool dungeon_server::domain::creature_status_manager::contains(const dungeon_common::enums::creature_status_type status)
{
    const auto it = std::ranges::find_if(statuses_, [&status](auto x)
    {
        return x->status_type == status;
    });

    return it != std::end(statuses_);
}

void dungeon_server::domain::creature_status_manager::on_begin_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log)
{
    std::ranges::for_each(statuses_, [&action_log, &encounter](auto status)
    {
        status->on_begin_of_turn(encounter, action_log);
    });
}

void dungeon_server::domain::creature_status_manager::on_end_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log)
{
    std::ranges::for_each(statuses_, [&action_log, &encounter](auto status)
    {
        status->on_end_of_turn(encounter, action_log);
    });

    std::erase_if(statuses_, [](auto status)
    {
        return status->quantity <= 0;
    });
}
