#include "client.h"
#include "Models/simple_answer_model.h"
using namespace dungeon_common;

void client::consult_spell(const char* spell)
{
    cout << "\nRetrieving knowledge from the Arcane realm for [" << spell << "] spell...\n";
    message<custom_msg_types> msg(custom_msg_types::spell_consult);

    //Copying to an array because we can't simply copy char* data
    char spell_array[40];
    strcpy_s(spell_array, spell);
    msg << spell_array;

    send(msg);
}

void client::validate_name(const char* name, function<void(simple_answer_model)> callback)
{
    message<custom_msg_types> msg(custom_msg_types::validate_name);

    //Copying to an array because we can't simply copy char* data
    char player_name[40] = "";
    strcpy_s(player_name, name);
    msg << player_name;

    validate_name_callback = callback;
    send(msg);
}

void client::create_player(const char* name)
{
    message<custom_msg_types> msg(custom_msg_types::create_player);

    //Copying to an array because we can't simply copy char* data
    char player_name[40] = "";
    strcpy_s(player_name, name);
    msg << player_name;
    
    send(msg);
}
