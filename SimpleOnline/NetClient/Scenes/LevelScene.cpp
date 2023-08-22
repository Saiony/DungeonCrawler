#include "LevelScene.h"
#include <iostream>
#include <chrono>

#include "game_over_loss_scene.h"
#include "game_over_win_scene.h"
#include "../Utility/custom_print.h"

dungeon_client::scene::level_scene::level_scene(const std::shared_ptr<client>& client_ptr)
{
    client_ptr_ = client_ptr;
}

void dungeon_client::scene::level_scene::show()
{
    client_ptr_->request_match_start([this](auto encounter)
    {
        print_combat(encounter);        
        handle_player_input(encounter);
    });

    while (true)
    {
    }
}

void dungeon_client::scene::level_scene::print_combat(const domain::encounter& encounter) const
{
    system("CLS");
    std::cout << "--- GAME SCENE ---" << std::endl << std::endl;

    std::cout << "-----------------------------------------" << std::endl;
    for (auto& enemy : encounter.enemies)
    {
        utility::custom_print::print_aligned(enemy.name, 30);
        std::cout << enemy.health << "/" << enemy.max_health << "hp" << std::endl;
    }
    std::cout << "-----------------------------------------" << std::endl;
    for (auto& player : encounter.players)
    {
        utility::custom_print::print_aligned(player.name, 30);
        std::cout << player.health << "/" << player.max_health << "hp" << std::endl;
    }
    std::cout << "-----------------------------------------" << std::endl;

    if (!encounter.log.empty())
    {
        std::cout << encounter.log << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }    

    if(encounter.game_over)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        on_game_over(encounter.players_won);
        return; 
    }
    
    if (encounter.check_active_player(client_ptr_->get_player()))
    {
        std::cout << "SKILLS" << std::endl;
        const auto actions = client_ptr_->get_player().actions;
        for(size_t i = 0; i < actions.size(); i++)
        {
            utility::custom_print::print_aligned("- " + actions[i].name, 20);

            if(i % 2 != 0)
                std::cout << std::endl;
        }
        
        std::cout << "Your turn..." << std::endl;
    }
    else
        std::cout << encounter.active_creature_ptr->name << "'s turn...";

    std::cout << std::endl;
}

void dungeon_client::scene::level_scene::handle_player_input(domain::encounter& encounter) const
{
    client_ptr_->read_input([this, &encounter](const std::string& input)
    {
        if (!encounter.check_active_player(client_ptr_->get_player()))
        {
            print_combat(encounter);
            std::cout << "Please wait your turn" << std::endl;
            handle_player_input(encounter);
        }

        const auto player_action_ptr = client_ptr_->get_player().get_action(input);

        if(player_action_ptr == nullptr)
        {
            print_combat(encounter);
            std::cout << "[" << input << "] is not on your action list" << std::endl;
            handle_player_input(encounter);
            return;
        }

        if(player_action_ptr->needs_target())
        {
            std::cout << "Type the target: " << std::endl;
            client_ptr_->read_input([&](const std::string& target_name)
            {
                const auto target_creature = encounter.get_creature(target_name);
                if(target_creature == nullptr)
                {
                    std::cout << "CREATURE NOT FOUND" << std::endl;
                    return;
                }
                
                client_ptr_->send_action(player_action_ptr->id, target_creature->public_id);
            });
        }        
    });
}


void dungeon_client::scene::level_scene::on_game_over(const bool players_won) const
{
    if(players_won)
    {
        game_over_win_scene win_scene;
        win_scene.show();
    }
    else
    {
        game_over_loss_scene loss_scene;
        loss_scene.show();
    }
}
