#include "client.h"

void client::consult_spell(const char* spell)
{
    cout << "\nRetrieving knowledge from the Arcane realm for [" << spell << "] spell...\n";
    dungeon::server::message<custom_msg_types> msg;
    msg.header.id = custom_msg_types::spell_consult;

    //Copying to an array because we can't simply copy char* data
    char spell_array[40];
    strcpy_s(spell_array, spell);
    msg << spell_array;

    send(msg);
}
