#include "CharacterCreationScene.h"
#include <iostream>

#include "LobbyScene.h"
#include "../../NetServer/Domain/Player.h"

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
    create_name();
}

void character_creation_scene::create_name()
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
            
            player_name_ = input;
            std::cout << std::endl << player_name_ << " is a beautiful name" << std::endl;
            create_class();
        });
    });
}

void character_creation_scene::create_class()
{
    client_ptr_->get_player_classes([&](auto classes)
    {
        std::cout << std::endl << "Now choose a class: " << std::endl;
        std::for_each(std::begin(classes), std::end(classes), [](auto player_class)
        {
            if(player_class.id == enums::player_class_type::unknown)
                return;
            
            std::cout << " - " << player_class.name << std::endl;
        });
        
        client_ptr_->read_input([&classes, this](auto answer)
        {
            auto answer_it = std::ranges::find_if(classes, [&answer](auto player_class){ return player_class.name == answer; });
            if(answer_it == std::end(classes))
            {
                std::cout << std::endl << "Please type a valid class" << std::endl;
                create_class();
            }

            player_class_ = (*answer_it).id;
            confirm_character_creation();
        });
    });
}

void character_creation_scene::confirm_character_creation()
{
    std::cout << "Confirm character creation? (yes/no)" << std::endl;
    client_ptr_->read_input([&](auto answer)
    {
        if (answer == "yes")
        {
            client_ptr_->create_player(player_name_, player_class_,[&](domain::player_complete player)
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
            std::cout <<  "Please type only yes or no";
            confirm_character_creation();
        }
    });
}

void character_creation_scene::on_character_created() const
{
    lobby_scene lobby_scene(client_ptr_);
    lobby_scene.show();
}
