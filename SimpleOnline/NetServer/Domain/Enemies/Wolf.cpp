#include "Wolf.h"
#include <iostream>

#include "NetServer/Domain/Actions/bite_action.h"

dungeon_server::domain::enemy::wolf::wolf(const std::string& new_name, const uint16_t new_health, const uint16_t new_damage, const uint16_t new_ability_power)
                                        : base_enemy(new_name, new_health, new_damage, new_ability_power)
{
}

std::string dungeon_server::domain::enemy::wolf::execute_turn(const std::shared_ptr<encounter>& encounter_ptr)
{
    auto it = encounter_ptr->players.cbegin();
    const int random = rand() % encounter_ptr->players.size();
    std::advance(it, random);

    const auto target_id = (*it)->public_id;
    action::bite_action action(dungeon_common::model::action_types::bite, public_id, target_id);
    auto action_log = action.use(encounter_ptr);

    return action_log;
}
