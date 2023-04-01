#include "client.h"
#include <thread>

#include "Models/simple_answer_model.h"
using namespace dungeon_common;
using namespace dungeon_common::model;

bool input_enabled = true;
bool quit = false;

void confirm_character_creation(const client& client, const string& name);
void create_character(client& client);

void handle_messages(client& client)
{
    while (true)
    {
        player_model player{};

        if (!client.is_connected())
        {
            cout << "Oracle is dead :(\n";
            return;
        }

        if (!client.incoming().empty())
        {
            auto msg = client.incoming().pop_front().msg;

            switch (msg.header.id)
            {
            case custom_msg_types::server_message:
                {
                    cout << "the oracle says...\n\n_______________________\n" << msg.body.data() <<
                        "\n_______________________\n\n";
                    msg >> player;
                    input_enabled = true;
                    break;
                }
            case custom_msg_types::validate_name:
                {
                    simple_answer_model answer;
                    msg >> answer;
                    client.validate_name_callback(answer);
                }
            default:
                break;
            }
        }
    }
}


void confirm_character_creation(client& client, const string& player_name)
{
    cout << "Confirm character creation? (Y/N)" << endl;
    string answer;
    cin >> answer;

    if (answer == "yes")
    {
        dungeon_common::message<custom_msg_types> msg(custom_msg_types::create_player);
        msg << player_name.c_str();
        
        client.send(msg);
    }
    else if (answer == "no")
        create_character(client);
    else
    {
        cout << "Invalid answer";
        confirm_character_creation(client, player_name);
    }
}

void create_character(client& client)
{
    cout << "Adventurer, what's your name?" << endl;

    string name;
    do
    {
        getline(cin, name);
    }
    while (name.empty());

    client.validate_name(name.c_str(),
             [name, &client](const simple_answer_model response)
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
                             create_character(client);
                             return;
                         }
                     default:
                         return;
                     }
                 }
                 cout << "Hello " << name << endl;
                 confirm_character_creation(client, name);
             });
}

int main()
{
    client client;
    client.connect("192.168.18.30", 60000);
    thread messages_thread(handle_messages, ref(client));

    cout << "<-~- . - ~-> DUNGEON CRAWLER <-~- . - ~->" << endl;
    create_character(client);

    while (true)
    {
    }
    return 0;
}
