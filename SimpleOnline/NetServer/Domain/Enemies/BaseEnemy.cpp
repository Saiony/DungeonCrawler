#include "BaseEnemy.h"
#include "Utility/guid_generator.h"
using namespace dungeon_server::domain;

base_enemy::base_enemy(const std::string& name, const uint16_t health, const uint16_t attack_damage, const uint16_t ability_power)
                        : base_creature(name, health, attack_damage, ability_power) 
{
    public_id = dungeon_common::utility::guid_generator::create_guid();
}




