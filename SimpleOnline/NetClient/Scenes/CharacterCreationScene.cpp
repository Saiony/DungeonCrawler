#include "CharacterCreationScene.h"
#include <iostream>

#include "LobbyScene.h"

using namespace dungeon_client::scene;
using namespace dungeon_common;


character_creation_scene::character_creation_scene(const shared_ptr<client>& client_ptr)
{
    client_ptr_ = client_ptr;
}

void character_creation_scene::show()
{
    create_character();    
}

void character_creation_scene::create_character()
{
    cout << "Adventurer, what's your name?" << endl;

    string name;
    do
    {
        getline(cin, name);
    }
    while (name.empty());

    client_ptr_->validate_name(name.c_str(),
                               [name, this](const simple_answer_model response)
                               {
                                   if (!response.ok)
                                   {
                                       switch (response.error_code)
                                       {
                                       case unknown:
                                           throw exception("Invalid message type");
                                       case(error_code_type::name_already_taken):
                                           {
                                               cout << "Sorry adventurer, the name is already taken" << endl;
                                               create_character();
                                               return;
                                           }
                                       default:
                                           return;
                                       }
                                   }
                                   cout << "Hello, " << name << endl;
                                   confirm_character_creation(name);
                               });
}

void character_creation_scene::confirm_character_creation(const string& player_name)
{
    cout << "Confirm character creation? (yes/no)" << endl;
    string answer;
    do
    {
        getline(cin, answer);
    }
    while (answer.empty());

    if (answer == "yes")
    {
        client_ptr_->create_player(player_name.c_str(), [this](model::player_model player_model)
        {
            domain::player player(player_model.id_, player_model.name_, player_model.health_);
            client_ptr_->set_player(player);
            cout << "Character created successfully";
            on_character_created();
        });      
    }
    else if (answer == "no")
        create_character();
    else
    {
        cout << "Please type only yes or no";
        confirm_character_creation(player_name);
    }
}

void character_creation_scene::on_character_created() const
{
    lobby_scene lobby_scene(client_ptr_);
    lobby_scene.show();
}
