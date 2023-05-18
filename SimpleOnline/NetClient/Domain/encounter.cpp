#include "encounter.h"

dungeon_client::domain::enemy::enemy(const char* name, const uint16_t health): name_(name), health_(health)
{
}

std::string dungeon_client::domain::enemy::get_name()
{
    return name_;
}

uint16_t dungeon_client::domain::enemy::get_health()
{
    return health_;
}

dungeon_client::domain::encounter::encounter(std::vector<enemy> enemies, std::vector<player> players) :
                                             enemies(std::move(enemies)), players(std::move(players))
{
}
