﻿#include "Encounter.h"
#include <algorithm>
#include <utility>
using namespace dungeon_server::domain;

encounter::encounter(std::vector<std::shared_ptr<base_enemy>> enemies, std::vector<std::shared_ptr<player>> players, std::shared_ptr<base_creature> active_creature)
                : enemies(std::move(enemies)), players(std::move(players)), active_creature(std::move(active_creature))
{
    std::ranges::for_each(this->players, [this](const std::shared_ptr<player>& player)
    {
        creatures.push_back(player);
    });

    std::ranges::for_each(this->enemies, [this](const std::shared_ptr<base_enemy>& enemy)
    {
        creatures.push_back(enemy);
    });
}

void encounter::go_to_next_turn()
{
    const auto it = std::ranges::find_if(creatures, [this](auto creature)
    {
        return creature->public_id == active_creature->public_id;
    });
    const auto next_it = std::next(it);
    
    if(next_it == std::end(creatures))
        active_creature = creatures[0];
    else
        active_creature = *next_it;
}
