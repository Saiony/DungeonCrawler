#include "CharacterCreationScene.h"
#include <iostream>

#include "LobbyScene.h"

using namespace dungeon_client::scene;
using namespace dungeon_common;


character_creation_scene::character_creation_scene(const std::shared_ptr<client>& client_ptr)
{
    client_ptr_ = client_ptr;
}

void character_creation_scene::show()
{
    create_character();
}

void character_creation_scene::create_character()
{
    std::cout << "Adventurer, what's your name?" << std::endl;

    client_ptr_->read_input([this](std::string input)
    {
        std::cout << "Name: " << input << std::endl;

        client_ptr_->validate_name(input.c_str(), [this, &input](model::simple_answer_model response)
        {
            if (!response.ok)
            {
                switch (response.error_code)
                {
                case error_code_type::unknown:
                    throw std::exception("Invalid message type");
                case(error_code_type::name_already_taken):
                    {
                        std::cout << "Sorry adventurer, the name is already taken" << std::endl;
                        create_character();
                        return;
                    }
                default:
                    return;
                }
            }
            std::cout << std::endl << input << " is a beautiful name" << std::endl;
            confirm_character_creation(input);
        });
    });
}

void character_creation_scene::confirm_character_creation(const std::string& player_name)
{
    std::cout << "Confirm character creation? (yes/no)" << std::endl;
    client_ptr_->read_input([&](std::string answer)
    {
        if (answer == "yes")
        {
            client_ptr_->create_player(player_name.c_str(), [&](domain::player_complete player)
            {   
                client_ptr_->set_player(player);
                std::cout << std::endl << "Character created successfully";
                on_character_created();
            });
        }
        else if (answer == "no")
            create_character();
        else
        {
            std::cout << "Please type only yes or no";
            confirm_character_creation(player_name);
        }
    });
}

void character_creation_scene::on_character_created() const
{
    lobby_scene lobby_scene(client_ptr_);
    lobby_scene.show();
}
