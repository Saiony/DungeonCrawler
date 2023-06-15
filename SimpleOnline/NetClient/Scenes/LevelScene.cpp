#include "LevelScene.h"
#include "Models/action_model.h"

dungeon_client::scene::level_scene::level_scene(const std::shared_ptr<client>& client_ptr)
{
    client_ptr_ = client_ptr;
}

void dungeon_client::scene::level_scene::show()
{
    client_ptr_->request_match_start([this](auto encounter)
    {
        print_combat(encounter);

        client_ptr_->read_input([this, &encounter](const std::string& input)
        {
            if (input == "sword slash")
                client_ptr_->send_action(dungeon_common::model::action_types::sword_slash, encounter.enemies[0].id);
        });
    });

    while(true){}
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

    if(encounter.check_active_player(client_ptr_->get_player()))
        std::cout << "Your turn...";
    else
        std::cout << encounter.active_creature_ptr->name << "'s turn...";

    std::cout << std::endl << std::endl;
}
