#include "Player.h"

dungeon_client::domain::player::player(): id(0), health(0)
{
}

dungeon_client::domain::player::player(const uint32_t id, std::string name, const uint32_t health): id(id), name(std::move(name)), health(health)
{
}
