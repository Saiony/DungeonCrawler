#include "LevelScene.h"
#include "Models/action_use_model.h"
#include <iostream>
#include <chrono>

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
        std::cout << enemy.name << " - " << enemy.health << "hp" << std::endl;
    }
    std::cout << "-----------------------------------------" << std::endl;
    for (auto& player : encounter.players)
    {
        std::cout << player.name << " - " << player.health << "hp" << std::endl;
    }
    std::cout << "-----------------------------------------" << std::endl;

    if (!encounter.log.empty())
    {
        std::cout << encounter.log << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    if (encounter.check_active_player(client_ptr_->get_player()))
        std::cout << "Your turn...";
    else
        std::cout << encounter.active_creature_ptr->name << "'s turn...";

    std::cout << std::endl << std::endl;
}

void dungeon_client::scene::level_scene::handle_wrong_turn_input(const domain::encounter& encounter) const
{
    client_ptr_->read_input([&encounter, this](const std::string& input)
    {
        print_combat(encounter);
        handle_wrong_turn_input(encounter);
    });
}

void dungeon_client::scene::level_scene::handle_player_input(const domain::encounter& encounter) const
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

        client_ptr_->send_action(player_action_ptr->id, encounter.enemies[0].public_id);
    });
}
