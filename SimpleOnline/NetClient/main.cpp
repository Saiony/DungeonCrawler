#include "client.h"
#include <thread>

#include "Domain/lobby_domain.h"
#include "Models/lobby_model.h"
#include "Scenes/CharacterCreationScene.h"

using namespace dungeon_common;
using namespace dungeon_client;

void handle_messages(const shared_ptr<client>& client_ptr)
{
    while (true)
    {
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
            case custom_msg_types::server_connection_response:
                {
                    model::simple_answer_model response;
                    msg >> response;

                    std::lock_guard l{client_ptr->mutex};
                    client_ptr->server_connection_response = response;
                    client_ptr->condition_var.notify_one();

                    break;
                }
            case custom_msg_types::validate_name:
                {
                    model::simple_answer_model response;
                    msg >> response;

                    std::lock_guard l{client_ptr->mutex};
                    client_ptr->validate_name_response = response;
                    client_ptr->condition_var.notify_one();

                    break;
                }
            case custom_msg_types::create_player:
                {
                    model::player_model response;
                    msg >> response;

                    std::lock_guard l{client_ptr->mutex};
                    client_ptr->create_player_response = response;
                    client_ptr->condition_var.notify_one();

                    break;
                }
            case custom_msg_types::player_ready_response:
                {
                    model::lobby_model response;
                    msg >> response;
                    const domain::lobby_domain lobby(response);

                    std::lock_guard l{client_ptr->mutex};

                    if (client_ptr->set_player_ready_callback != nullptr)
                        client_ptr->set_player_ready_callback(lobby);

                    client_ptr->set_player_ready_response = lobby;
                    client_ptr->condition_var.notify_one();

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
    thread messages_thread(handle_messages, ref(client_ptr));
    client_ptr->connect("192.168.18.30", 60000);

    //locks thread and waits for condition var
    std::unique_lock lock{client_ptr->mutex};
    client_ptr->condition_var.wait(lock);
    const auto server_connection_response = client_ptr->server_connection_response;
    lock.unlock();

    if (!server_connection_response.ok)
    {
        switch (server_connection_response.error_code)
        {
        case server_full:
                cout << "Server full, please wait for someone to disconnect";
                break;
        default:
                cout << "Couldn't connect to server. Unknown error";
                break;
        }

        messages_thread.join();
        return 0;
    }

    cout << "<-~- . - ~-> DUNGEON CRAWLER <-~- . - ~->" << endl;
    scene::character_creation_scene character_creation_scene(client_ptr);
    thread game_thread(&scene::character_creation_scene::show, &character_creation_scene);

    messages_thread.join();

    while (true)
    {
    }
}
