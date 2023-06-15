﻿#include "Wolf.h"
#include <iostream>

#include "NetServer/Domain/Actions/bite_action.h"

dungeon_server::domain::enemy::wolf::wolf(const std::string& name, const uint16_t health, const uint16_t damage) : base_enemy(name, health, damage)
{
}

void dungeon_server::domain::enemy::wolf::execute_turn(const std::shared_ptr<encounter>& encounter_ptr)
{
    auto it = encounter_ptr->players.cbegin();
    const int random = rand() % encounter_ptr->players.size();
    std::advance(it, random);

    const auto target_id = (*it)->public_id;
    action::bite_action action(dungeon_common::model::action_types::bite, target_id);
    action.use(encounter_ptr);
}
