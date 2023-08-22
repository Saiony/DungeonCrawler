#include "enemy.h"

dungeon_client::domain::enemy::enemy(const char* id, const char* name, const uint16_t health, const uint16_t max_health)
                                    : base_creature(id, name, health, max_health)
{
}