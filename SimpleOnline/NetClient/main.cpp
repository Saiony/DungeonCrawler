#include "client.h"
#include <thread>

#include "Scenes/CharacterCreationScene.h"

using namespace dungeon_common;
using namespace dungeon_client;

void handle_messages(const shared_ptr<client>& client_ptr)
{
    while (true)
    {
        if (!client_ptr->is_connected())
        {
            std::cout << "Oracle is dead :(\n";
            return;
        }

        if (!client_ptr->incoming().empty())
        {
            auto msg = client_ptr->incoming().pop_front().msg;

            switch (msg.header.id)
            {
            case custom_msg_types::server_message:
                {
                    model::player_model player{};
                    msg >> player;
                    break;
                }
            case custom_msg_types::validate_name:
                {
                    simple_answer_model answer;
                    msg >> answer;
                    client_ptr->validate_name_callback(answer);
                    break;
                }
            case custom_msg_types::create_player:
                {
                    model::player_model player_model;
                    msg >> player_model;
                    client_ptr->create_player_callback(player_model);
                    break;
                }
            default:
                break;
            }
        }
    }
}

int main()
{
    auto client_ptr = make_shared<client>();
    client_ptr->connect("192.168.18.30", 60000);
    thread messages_thread(handle_messages, ref(client_ptr));

    cout << "<-~- . - ~-> DUNGEON CRAWLER <-~- . - ~->" << endl;
    scene::character_creation_scene character_creation_scene(client_ptr);
    character_creation_scene.init();

    while (true)
    {
    }
    return 0;
}
