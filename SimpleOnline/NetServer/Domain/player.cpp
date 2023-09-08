#include "player.h"
#include <iostream>
#include <utility>
#include "Utility/guid_generator.h"

void dungeon_server::domain::player::do_something() const
{
    std::cout << "My id is " << private_id << std::endl;
}

dungeon_server::domain::player::player(std::string client_id, const std::string& new_name, domain::player_class player_class,
                                       const uint16_t new_health, const uint16_t new_damage,
                                       const uint16_t new_ability_power, std::vector<dungeon_common::model::action_types> actions,
                                       const dungeon_common::enums::elemental_property_type elemental_property)
                                       : base_creature(new_name, new_health, new_damage, new_ability_power, elemental_property),
                                       private_id(std::move(client_id)), aggro(1),
                                       player_class(std::move(player_class)), actions(std::move(actions))
{
    public_id = dungeon_common::utility::guid_generator::create_guid();
}
