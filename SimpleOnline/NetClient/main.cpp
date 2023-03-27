#include "client.h"
using namespace dungeon_common::model;


bool input_enabled = true;
bool quit = false;

void handle_messages(client& client)
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
        
            cout << "the oracle says...\n\n_______________________\n" << msg.body.data() << "\n_______________________\n\n";
            msg >> player;
            input_enabled = true;
            break;
        default:
            break;
        }
    }
}

int main()
{
    client client;

    client.connect("192.168.18.30", 60000);

    cout << "<-~- . - ~-> DUNGEON CRAWLER <-~- . - ~->" << endl;
    cout << "Adventurer, what's your name?" << endl;
    

    while (!quit)
    {
        handle_messages(client);

        if (input_enabled)
        {
            input_enabled = false;
            string input;
            cin >> input;

            if(input.empty())
                continue;

            client.validate_name(input.c_str());
            input_enabled = true;
        }
    }

    return 0;
}
