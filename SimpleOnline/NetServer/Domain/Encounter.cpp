#include "Encounter.h"

#include <utility>
using namespace  dungeon_server::domain::encounter;

encounter::encounter(std::vector<enemy::base_enemy> enemies) : enemies_(std::move(enemies))
{
}
