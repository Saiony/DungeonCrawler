#include "Encounter.h"
#include <algorithm>
#include <utility>
using namespace dungeon_server::domain;

encounter::encounter(std::vector<enemy::base_enemy> enemies, std::vector<player> players, base_creature active_creature)
                : enemies(std::move(enemies)), players(std::move(players)), active_creature(std::move(active_creature))
{
    std::ranges::for_each(players, [this](const player& player)
    {
        creatures.push_back(std::make_shared<base_creature>(player));
    });

    std::ranges::for_each(enemies, [this](const enemy::base_enemy& enemy)
    {
        creatures.push_back(std::make_shared<base_creature>(enemy));
    });
}
