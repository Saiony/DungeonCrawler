#include "encounter_manager.h"

#include <iostream>

#include "Domain/Enemies/goblin_archer.h"
#include "Domain/Enemies/goblin_warrior.h"
#include "Domain/Enemies/Wolf.h"
#include "Domain/Status/base_creature_status.h"
#include "Domain/Status/stunned_status.h"

dungeon_server::domain::encounter_manager::encounter_manager(std::vector<std::shared_ptr<player>> players)
                                            : level_(1), players_(std::move(players)), current_encounter(generate_encounter())
{
}

std::shared_ptr<dungeon_server::domain::encounter> dungeon_server::domain::encounter_manager::generate_encounter() const
{
    std::vector<std::shared_ptr<base_enemy>> enemies;
    switch (level_)
    {
    case 1:
        {
            enemies.push_back(std::make_shared<enemy::wolf>("wolf", 10, 5, 1,
                                                                dungeon_common::enums::elemental_property_type::normal));
            break;
        }
    case 2:
        {
            enemies.push_back(std::make_shared<enemy::goblin_warrior>("goblin warrior", 25, 3, 1,
                                                                          dungeon_common::enums::elemental_property_type::earth));
            enemies.push_back(std::make_shared<enemy::goblin_archer>("goblin archer", 15, 6, 1,
                                                                         dungeon_common::enums::elemental_property_type::earth));
            break;
        }
    default:
        {
            throw std::exception("invalid level");
        }
    }
    
    return std::make_shared<encounter>(enemies, players_, players_[0]);
}

void dungeon_server::domain::encounter_manager::go_to_next_encounter()
{
    level_++;
    if(level_ > max_level_)
    {        
        std::cout << "GAME OVER - PLAYERS WON" << std::endl;
        current_encounter->set_game_over(true);
        return;
    }    
    current_encounter = generate_encounter();
}

void dungeon_server::domain::encounter_manager::remove_dead_creatures() const
{
    std::erase_if(current_encounter->creatures, [](auto creature)
    {
        return creature->alive == false;
    });

    std::erase_if(current_encounter->players, [](auto player)
    {
        return player->alive == false;
    });
            
    std::erase_if(current_encounter->enemies, [](auto enemy)
    {
        return enemy->alive == false;
    });
}

void dungeon_server::domain::encounter_manager::go_to_next_turn()
{
    remove_dead_creatures();
    if(current_encounter->players.empty())
    {
        std::cout << "GAME OVER - PLAYERS LOST" << std::endl;
        current_encounter->set_game_over(false);
    }
    else if(current_encounter->enemies.empty())
    {
        std::cout << "ENCOUNTER END - PLAYERS WON" << std::endl;
        go_to_next_encounter();        
    }
    else
        current_encounter->go_to_next_turn();
}
