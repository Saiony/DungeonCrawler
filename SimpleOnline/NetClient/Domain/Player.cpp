#include "Player.h"

dungeon_client::domain::player::player() : base_creature()
{
}

dungeon_client::domain::player::player(const std::string& id, const std::string& name, const uint32_t health) : base_creature(id, name, health)
{
}
