#include "BaseEnemy.h"

#include "NetServer/Domain/Actions/heal_action.h"
using namespace dungeon_server::domain::enemy;

base_enemy::base_enemy(std::string name, const uint16_t health, const uint16_t damage): id_("enemy-"), name_(name), health_(health), damage_(damage)
{
    id_.append(name);
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
