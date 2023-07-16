#include "encounter_manager.h"
#include "Domain/Enemies/Wolf.h"

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
            const enemy::wolf wolf("wolf", 10, 5, 1);
            enemies.push_back(std::make_shared<enemy::wolf>(wolf));
            break;
        }
    case 2:
        {
            const enemy::wolf wolf("wolf 1", 10, 5, 1);
            const enemy::wolf wolf2("wolf 2", 10, 5, 1);
            enemies.push_back(std::make_shared<enemy::wolf>(wolf));
            enemies.push_back(std::make_shared<enemy::wolf>(wolf2));
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
        std::cout << "GAME OVER" << std::endl;
    }
    else if(current_encounter->enemies.empty())
    {
        std::cout << "PLAYERS WIN" << std::endl;
        go_to_next_encounter();        
    }
    else
        current_encounter->go_to_next_turn();
}
