#include "BaseEnemy.h"
using namespace dungeon_server::domain::enemy;

base_enemy::base_enemy(const char* name, const uint16_t health, const uint16_t damage): id_("enemy-"), name_(name), health_(health), damage_(damage)
{
    id_.append(name);
}

void base_enemy::execute_turn()
{
}
