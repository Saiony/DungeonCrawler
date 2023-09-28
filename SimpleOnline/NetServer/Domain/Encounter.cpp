#include "Encounter.h"
#include <algorithm>
#include <utility>
using namespace dungeon_server::domain;

encounter::encounter(std::vector<std::shared_ptr<base_enemy>> enemies,
                     std::vector<std::shared_ptr<player>> players,
                     std::shared_ptr<base_creature> active_creature)
    : players(std::move(players)),
      active_creature(std::move(active_creature))
{
    std::ranges::for_each(this->players, [this](const std::shared_ptr<player>& player)
    {
        creatures.push_back(player);
        player->add_on_creature_died_listener([this](auto creature)
        {
            on_creature_died(creature);
        });
    });

    std::ranges::for_each(enemies, [this](const std::shared_ptr<base_enemy>& enemy)
    {
        add_enemy(enemy);
        enemy->add_on_creature_died_listener([this](auto creature)
        {
            on_creature_died(creature);
        });
    });

    std::cout << "\nEncounter created";
}

void encounter::subscribe_players_lost(const std::function<void()>& callback)
{
    on_players_lost_callback_ = callback;
}

void encounter::go_to_next_turn()
{
    const auto it = std::ranges::find_if(creatures, [this](auto creature)
    {
        return creature->public_id == active_creature->public_id;
    });
    const auto next_it = std::next(it);

    if (next_it >= std::end(creatures))
        active_creature = creatures[0];
    else
        active_creature = *next_it;
}

void encounter::set_game_over(const bool players_won_encounter)
{
    combat_ended = true;
    this->players_won = players_won_encounter;
}

void encounter::on_creature_died(const std::shared_ptr<base_creature>& creature)
{
    if (creature->alive)
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

    check_encounter_ended();
}

void encounter::check_encounter_ended()
{
    if (players.empty())
    {
        std::cout << "\nGAME OVER - PLAYERS LOST" << std::endl;
        combat_ended = true;
        on_players_lost_callback_();
    }
    
    if (enemies.empty())
    {
        combat_ended = true;
    }
}

void encounter::add_enemy(const std::shared_ptr<base_enemy>& new_enemy)
{
    const int repeated_name_creature = std::ranges::count_if(enemies, [this, new_enemy](auto enemy)
    {
        return enemy->get_base_name() == new_enemy->get_base_name();
    });

    new_enemy->name = new_enemy->get_base_name();
    
    if (repeated_name_creature > 0)
        new_enemy->name += " " + std::to_string(repeated_name_creature + 1);

    creatures.push_back(new_enemy);
    enemies.push_back(new_enemy);
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
