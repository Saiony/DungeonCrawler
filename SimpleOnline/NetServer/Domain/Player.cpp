﻿#include "Player.h"
#include <iostream>
#include <utility>
#include "Utility/guid_generator.h"

void dungeon_server::domain::player::do_something() const
{
    std::cout << "My id is " << private_id << std::endl;
}

dungeon_server::domain::player::player(std::string client_id, const std::string& new_name, const uint16_t new_health, const uint16_t new_damage,
                                       const uint16_t new_ability_power, std::vector<dungeon_common::model::action_types> actions)
               : base_creature(new_name, new_health, new_damage, new_ability_power),
                 private_id(std::move(client_id)), actions(std::move(actions))
{
    public_id = dungeon_common::utility::guid_generator::create_guid();
}
