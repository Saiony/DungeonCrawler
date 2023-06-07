#include "Encounter.h"
#include <algorithm>
#include <utility>
using namespace  dungeon_server::domain::encounter;

encounter::encounter(std::vector<enemy::base_enemy> enemies, std::vector<player> players)
                : enemies(std::move(enemies)), players(std::move(players))
{
    std::ranges::for_each(players, [this](const player& player)
    {
        creatures.push_back(std::make_unique<base_creature>(player));
    });

    std::ranges::for_each(enemies, [this](const enemy::base_enemy& enemy)
    {
        creatures.push_back(std::make_unique<base_creature>(enemy));
    });
}
