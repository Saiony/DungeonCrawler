#include "Player.h"

dungeon_client::domain::player::player() : base_creature()
{
}

dungeon_client::domain::player::player(const std::string& id, const std::string& name, player_class player_class, const uint32_t health)
                                       : base_creature(id, name, health), my_class(std::move(player_class))
{
}
