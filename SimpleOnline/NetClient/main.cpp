#include "client.h"
#include <thread>

#include "Domain/lobby_domain.h"
#include "Models/lobby_model.h"
#include "Scenes/CharacterCreationScene.h"

using namespace dungeon_common;
using namespace dungeon_client;


void handle_connection_error(error_code_type error_code)
{
    switch (error_code)
    {
    case server_full:
        cout << "Server full, please wait for someone to disconnect";
        break;
    default:
        cout << "Couldn't connect to server. Unknown error";
        break;
    }
}

int main()
{
    cout << "<-~- . - ~-> DUNGEON CRAWLER <-~- . - ~->" << endl << endl;
    auto client_ptr = make_shared<client>();
    client_ptr->connect("192.168.18.30", 60000);
    client_ptr->init();

    client_ptr->connection_callback = [&client_ptr](model::simple_answer_model response)
    {
        if (!response.ok)
        {
            handle_connection_error(response.error_code);
            return;
        }
        scene::character_creation_scene character_creation_scene(client_ptr);
        character_creation_scene.show();
    };
    
    client_ptr->wait_message();    
    client_ptr->end();
    while (true)
    {
    }
}
