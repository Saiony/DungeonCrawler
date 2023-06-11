﻿#include "LevelScene.h"
#include "Models/action_model.h"

dungeon_client::scene::level_scene::level_scene(const std::shared_ptr<client>& client_ptr)
{
    client_ptr_ = client_ptr;
}

void dungeon_client::scene::level_scene::show()
{
    client_ptr_->request_match_start([this](auto encounter)
    {
        system("CLS");
        std::cout << "--- GAME SCENE ---" << std::endl << std::endl;

        std::cout << "-----------------------------------------" << std::endl;
        for (auto& enemy : encounter.enemies)
        {
            std::cout << enemy.get_name() << " - " << enemy.get_health() << "hp" << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;
        for (auto& player : encounter.players)
        {
            std::cout << player.get_name() << " - " << player.get_health() << "hp" << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;

        std::cout << "Active player: " << encounter.active_creature_ptr->get_name() << std::endl << std::endl;

        client_ptr_->read_input([this, &encounter](const std::string& input)
        {
            if (input == "sword slash")
                client_ptr_->send_action(dungeon_common::model::action_types::sword_slash, encounter.enemies[0].get_id());
        });
    });

    while(true){}
}
