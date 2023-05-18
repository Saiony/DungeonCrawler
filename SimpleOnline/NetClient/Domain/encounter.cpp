#include "encounter.h"

dungeon_client::domain::enemy::enemy(const char* name, const uint16_t health): name_(name), health_(health)
{
}

dungeon_client::domain::encounter::encounter(std::vector<enemy> enemies, std::vector<player> players) :
                                             enemies_(std::move(enemies)), players_(std::move(players))
{
}
