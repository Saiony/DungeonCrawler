#include "BaseEnemy.h"
#include "Utility/guid_generator.h"
using namespace dungeon_server::domain;

base_enemy::base_enemy(const std::string& name, const uint16_t health, const uint16_t damage) : base_creature(name, health, damage) 
{
    public_id = dungeon_common::utility::guid_generator::create_guid();
}




