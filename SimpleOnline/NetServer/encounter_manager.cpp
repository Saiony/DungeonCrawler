#include "encounter_manager.h"

#include <iostream>
#include <utility>

#include "Domain/Enemies/goblin_archer.h"
#include "Domain/Enemies/goblin_warrior.h"
#include "Domain/Enemies/Wolf.h"

dungeon_server::domain::encounter_manager::encounter_manager(std::vector<std::shared_ptr<player>> players)
                                            : level_(1), players_(std::move(players)), current_encounter(generate_encounter())
{    
}

void dungeon_server::domain::encounter_manager::add_encounter_end_listener(std::function<void(bool)> callback)
{
    encounter_end_callback_ = std::move(callback);
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

void dungeon_server::domain::encounter_manager::end_encounter()
{
    level_++;
    
    if(level_ > max_level_)
    {        
        std::cout << "GAME OVER - PLAYERS WON" << std::endl;
        current_encounter->set_game_over(true);
    }
}

void dungeon_server::domain::encounter_manager::start_encounter()
{
    if(level_ > max_level_)
        return;
    
    current_encounter = generate_encounter();
}

void dungeon_server::domain::encounter_manager::go_to_next_turn() const
{
    if(current_encounter->players.empty())
    {
        std::cout << "GAME OVER - PLAYERS LOST" << std::endl;
        encounter_end_callback_(false);
    }
    else if(current_encounter->enemies.empty())
    {
        std::cout << "ENCOUNTER END - PLAYERS WON" << std::endl;
        encounter_end_callback_(true);   
    }
}
