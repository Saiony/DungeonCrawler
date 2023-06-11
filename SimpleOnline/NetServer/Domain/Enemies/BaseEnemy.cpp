#include "BaseEnemy.h"
#include "Utility/guid_generator.h"
using namespace dungeon_server::domain::enemy;

base_enemy::base_enemy(std::string name, const uint16_t health, const uint16_t damage): name_(std::move(name)), health_(health), damage_(damage)
{
    public_id = dungeon_common::utility::guid_generator::create_guid();
}

void base_enemy::execute_turn()
{
}

std::string base_enemy::get_name() const
{
    return name_;
}

uint16_t base_enemy::get_health() const
{
    return health_;
}

std::string base_enemy::get_id() const
{
    return public_id;
}

void base_enemy::take_damage(const int damage)
{
    health_ -= damage;
}
