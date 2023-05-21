#include "Player.h"

dungeon_client::domain::player::player() = default;

dungeon_client::domain::player::player(std::string id, std::string name, const uint32_t health): id(std::move(id)), name(std::move(name)), health(health)
{
}
