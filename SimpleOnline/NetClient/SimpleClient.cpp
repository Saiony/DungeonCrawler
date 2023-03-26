#include<iostream>
#include<dungeon_network.h>

#include "Models/player_model.h"

using namespace dungeon::server;

enum class custom_msg_types : uint32_t
{
    server_accept,
    server_deny,
    spell_consult,
    message_all,
    server_message,
};

class custom_client : public client_interface<custom_msg_types>
{
public:
    void consult_spell(const char* spell)
    {
        cout << "\nRetrieving knowledge from the Arcane realm for [" << spell << "] spell...\n";
        message<custom_msg_types> msg;
        msg.header.id = custom_msg_types::spell_consult;

        //Copying to an array because we can't simply copy char* data
        char spell_array[40];
        strcpy_s(spell_array, spell);
        msg << spell_array;

        send(msg);
    }
};

void handle_input(custom_client& client);
void handle_messages(custom_client& client);
bool input_enabled = true;
bool quit = false;

int main()
{
    custom_client client;

    client.connect("192.168.18.30", 60000);

    cout << "<-~- . - ~-> D&D SPELL CONSULT <-~- . - ~->";
    cout << "\n1 - Burning Hands \n2 - Charm Person \n3 - Cure Wounds \n4 - Mage Armor \n5 - Thunderwave\n0 - Quit Application\n\n";

    while (!quit)
    {
        handle_messages(client);

        // if (inputEnabled)
        // 	handle_input(client);
    }

    return 0;
}

void handle_input(custom_client& client)
{
    int input;
    cout << "[Type your wish] - ";
    cin >> input;
    input_enabled = false;

    switch (input)
    {
    case 0:
        quit = true;
        break;
    case 1:
        client.consult_spell("BurningHands");
        break;
    case 2:
        client.consult_spell("CharmPerson");
        break;
    case 3:
        client.consult_spell("CureWounds");
        break;
    case 4:
        client.consult_spell("MageArmor");
        break;
    case 5:
        client.consult_spell("Thunderwave");
        break;
    default:
        cout << "Please type a number between 1 and 5";
        break;
    }
}

void handle_messages(custom_client& client)
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
