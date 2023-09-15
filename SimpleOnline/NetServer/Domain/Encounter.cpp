#include "Encounter.h"
#include <algorithm>
#include <utility>
using namespace dungeon_server::domain;

encounter::encounter(std::vector<std::shared_ptr<base_enemy>> enemies, std::vector<std::shared_ptr<player>> players, std::shared_ptr<base_creature> active_creature)
                : enemies(std::move(enemies)), players(std::move(players)), active_creature(std::move(active_creature))
{
    std::ranges::for_each(this->players, [this](const std::shared_ptr<player>& player)
    {
        creatures.push_back(player);
        player->add_on_creature_died_listener([this](auto creature)
        {
            on_creature_died(creature);
        });
    });

    std::ranges::for_each(this->enemies, [this](const std::shared_ptr<base_enemy>& enemy)
    {
        creatures.push_back(enemy);
        enemy->add_on_creature_died_listener([this](auto creature)
        {
            on_creature_died(creature);
        });
    });
}

void encounter::go_to_next_turn()
{
    const auto it = std::ranges::find_if(creatures, [this](auto creature)
    {
        return creature->public_id == active_creature->public_id;
    });
    const auto next_it = std::next(it);
    
    if(next_it >= std::end(creatures))
        active_creature = creatures[0];
    else
        active_creature = *next_it;
}

void encounter::set_game_over(const bool players_won_encounter)
{
    game_over = true;
    this->players_won = players_won_encounter;
}

void encounter::on_creature_died(const std::shared_ptr<base_creature>& creature)
{
    if(creature->alive)
        throw std::exception("Trying to kill an alive creature");

    std::erase_if(creatures, [&creature](auto base_creature)
    {
        return base_creature->public_id == creature->public_id;
    });

    std::erase_if(players, [&creature](auto player)
    {
        return player->public_id == creature->public_id;
    });
            
    std::erase_if(enemies, [&creature](auto enemy)
    {
        return enemy->public_id == creature->public_id;
    });
}

std::shared_ptr<base_creature> encounter::get_creature(const std::string& creature_id)
{
    auto action_owner = *std::ranges::find_if(creatures, [this, &creature_id](auto creature)
    {
       return creature->public_id == creature_id;
    });

    return action_owner;
}

std::shared_ptr<player> encounter::get_player(const std::string& player_id)
{
    auto action_owner = *std::ranges::find_if(players, [this, &player_id](auto player)
    {
       return player->public_id == player_id;
    });

    return action_owner;
}