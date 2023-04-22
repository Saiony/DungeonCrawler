#include "client.h"
#include "Models/simple_answer_model.h"
using namespace dungeon_common;
using namespace dungeon_client;

void client::validate_name(const char* name)
{
    message<custom_msg_types> msg(custom_msg_types::validate_name);

    //Copying to an array because we can't simply copy char* data
    char player_name[40] = "";
    strcpy_s(player_name, name);
    msg << player_name;
    
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

void client::set_player(domain::player& player)
{
     player_ = move(player);
}

void client::set_player_ready(const bool ready, const function<void(domain::lobby_domain)>& callback)
{
    message<custom_msg_types> msg(custom_msg_types::player_ready);
    msg << ready;

    set_player_ready_callback = callback;
    send(msg);
}
