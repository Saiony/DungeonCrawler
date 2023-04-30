#include "client.h"

#include <conio.h>

#include "Models/simple_answer_model.h"
using namespace dungeon_common;
using namespace dungeon_client;

string player_input;
thread input_thread;

void read_input_thread(string& input)
{
    while (true)
    {
        string x;
        getline(cin, x);
        input = x;
    }
}

void client::init()
{
    input_thread = thread(read_input_thread, ref(player_input));
}

void client::end()
{
    input_thread.join();
}

void client::validate_name(const char* name, const function<void(model::simple_answer_model)>& callback)
{
    message<custom_msg_types> msg(custom_msg_types::validate_name);

    //Copying to an array because we can't simply copy char* data
    char player_name[40] = "";
    strcpy_s(player_name, name);
    msg << player_name;

    validate_name_callback = callback;
    send(msg);
}

void client::create_player(const char* name, const function<void(dungeon_common::model::player_model)>& callback)
{
    message<custom_msg_types> msg(custom_msg_types::create_player);

    //Copying to an array because we can't simply copy char* data
    char player_name[40] = "";
    strcpy_s(player_name, name);
    msg << player_name;

    create_player_callback = callback;
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

void client::read_input(const function<void(string input)>& callback)
{
    player_input.clear();
    player_input_callback = callback;

    while (true)
    {
        if (!player_input.empty())
        {
            if (player_input_callback != nullptr)
            {
                player_input_callback(player_input);
                player_input_callback = nullptr;
            }
            return;
        }

        if (handle_messages())
            return;
    }
}

void client::wait_message()
{
    while (true)
    {
        if (handle_messages())
            return;
    }
}

bool client::handle_messages()
{
    if (incoming().empty())
        return false;

    auto msg = incoming().pop_front().msg;

    switch (msg.header.id)
    {
    case custom_msg_types::server_message:
        {
            model::player_model player{};
            msg >> player;

            return true;
        }
    case custom_msg_types::server_connection_response:
        {
            model::simple_answer_model response;
            msg >> response;

            if (connection_callback != nullptr)
            {
                connection_callback(response);
                return true;
            }
            return false;
        }
    case custom_msg_types::validate_name:
        {
            model::simple_answer_model response;
            msg >> response;

            if (validate_name_callback != nullptr)
            {
                validate_name_callback(response);
                return true;
            }
            return false;
        }
    case custom_msg_types::create_player:
        {
            model::player_model response;
            msg >> response;

            if (create_player_callback != nullptr)
            {
                create_player_callback(response);
                return true;
            }
            return false;
        }
    case custom_msg_types::player_ready_response:
        {
            model::lobby_model response;
            msg >> response;
            const domain::lobby_domain lobby(response);

            if (set_player_ready_callback != nullptr)
            {
                set_player_ready_callback(lobby);
                return true;
            }
            return false;
        }
    default:
        return false;
    }
}
