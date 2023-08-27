#include "stunned_status.h"

#include <iostream>

#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::stunned_status::stunned_status(const dungeon_common::enums::creature_status_type status_type, const uint8_t quantity,
                                                       const std::string& creature_id)
                                                               : base_creature_status(status_type, quantity, creature_id)
{
}

void dungeon_server::domain::stunned_status::on_begin_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log)
{
    const auto this_creature = std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });
    action_log += "\n" + (*this_creature)->name + " is stunned";
}

void dungeon_server::domain::stunned_status::on_end_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log)
{
    quantity--;
}
