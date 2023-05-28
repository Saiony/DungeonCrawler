#include "LevelScene.h"
#include "Models/action_model.h"

dungeon_client::scene::level_scene::level_scene(const std::shared_ptr<client>& client_ptr)
{
    client_ptr_ = client_ptr;
}

void dungeon_client::scene::level_scene::show()
{
    system("CLS");
    std::cout << "--- GAME SCENE ---" << std::endl << std::endl;

    client_ptr_->get_encounter([](auto encounter)
    {
        for (auto& enemy : encounter.enemies)
        {
            std::cout << enemy.get_name() << " - " << enemy.get_health() << "hp" << std::endl << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl << std::endl;
        for (auto& player : encounter.players)
        {
            std::cout << player.name << " - " << player.health << "hp" << std::endl;
        }
    });

    std::string input;
    while (true)
    {
        client_ptr_->read_input([this](std::string input)
        {
            if (input == "heal")
                client_ptr_->send_action(action_types::heal, 1);
            else if (input == "sword slash")
                client_ptr_->send_action(action_types::sword_slash, 1);
        });
    }
}
