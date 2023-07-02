#include "client.h"
#include <thread>
#include "Scenes/CharacterCreationScene.h"

using namespace dungeon_common;
using namespace dungeon_client;


void handle_connection_error(error_code_type error_code)
{
    switch (error_code)
    {
    case error_code_type::server_full:
        std::cout << "Server full, please wait for someone to disconnect";
        break;
    default:
        std::cout << "Couldn't connect to server. Unknown error";
        break;
    }
}

int main()
{
    std::cout << "<-~- . - ~-> DUNGEON CRAWLER <-~- . - ~->" << std::endl << std::endl;
    auto client_ptr = std::make_shared<client>();
    client_ptr->connect("192.168.15.127", 14414, [&client_ptr](const model::simple_answer_model response)
    {
        if (!response.ok)
        {
            handle_connection_error(response.error_code);
            return;
        }
        scene::character_creation_scene character_creation_scene(client_ptr);
        character_creation_scene.show();
    });
    
    client_ptr->end();
}
