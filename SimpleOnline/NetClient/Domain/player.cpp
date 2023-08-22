#include "player.h"

dungeon_client::domain::player::player() : base_creature()
{
}

dungeon_client::domain::player::player(const std::string& id, const std::string& name, player_class player_class,
                                       const uint16_t health, const uint16_t max_health)
                                       : base_creature(id, name, health, max_health), my_class(std::move(player_class))
{
}
