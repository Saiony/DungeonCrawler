#include "encounter_manager.h"

#include <iostream>
#include <utility>

#include "Enemies/giant_spider.h"
#include "Enemies/goblin_archer.h"
#include "Enemies/goblin_warrior.h"
#include "Enemies/Wolf.h"

dungeon_server::domain::encounter_manager::encounter_manager(std::vector<std::shared_ptr<player>> players)
    : players_(std::move(players))
{
}

std::shared_ptr<dungeon_server::domain::encounter> dungeon_server::domain::encounter_manager::generate_encounter(const uint8_t level) const
{
    std::cout << "\nGenerating new encounter...";
    std::vector<std::shared_ptr<base_enemy>> enemies;

    switch (level)
    {
    case 1:
        {
            enemies.push_back(std::make_shared<enemy::wolf>(10, 5, 1));
            break;
        }
    case 2:
        {
            enemies.push_back(std::make_shared<enemy::goblin_warrior>(25, 3, 1));
            enemies.push_back(std::make_shared<enemy::goblin_archer>(15, 6, 1));
            break;
        }
    case 3:
        {
            enemies.push_back(std::make_shared<enemy::giant_spider>(20, 4, 1));
            enemies.push_back(std::make_shared<enemy::giant_spider>(20, 4, 1));
            break;
        }
    default:
        {
            throw std::exception("invalid level");
        }
    }

    std::cout << "\nGenerating new encounter 2...";
    return std::make_shared<encounter>(enemies, players_, players_[0]);
}

void dungeon_server::domain::encounter_manager::start_encounter(const uint8_t level)
{
    if (level > max_level_)
        return;

    current_encounter = generate_encounter(level);
}

bool dungeon_server::domain::encounter_manager::go_to_next_turn(action_log& action_log) const
{
    if(current_encounter->combat_ended)
        return false;
    
    current_encounter->go_to_next_turn();
    return true;
}
