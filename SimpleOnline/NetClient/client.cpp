#include "client.h"

#include "Models/action_model.h"
#include "Models/encounter_model.h"
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

client::client()
{
    input_thread = thread(read_input_thread, ref(player_input));
}

void client::end() const
{
    input_thread.join();
}

void client::connect(const string& host, const uint16_t port, const function<void(dungeon_common::model::simple_answer_model)>& callback)
{
    base_client::connect(host, port);
    connection_callback = callback;
    wait_message();
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
    wait_message();
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
    wait_message();
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
    wait_message();
}

void client::send_action(const action_types action_id, int target_id)
{
    const action_model action(action_id, 1);
    message<custom_msg_types> msg(custom_msg_types::player_action);

    msg << action;
    send(msg);
}

void client::get_encounter(const function<void(domain::encounter)>& callback)
{
    get_encounter_callback = callback;
    const message<custom_msg_types> msg(custom_msg_types::match_start_request);
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
                connection_callback = nullptr;
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
                validate_name_callback = nullptr;
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
                create_player_callback = nullptr;
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
                set_player_ready_callback = nullptr;
                return true;
            }
            return false;
        }
    case custom_msg_types::match_start_response:
        {
            model::encounter_model encounter_model;
            msg >> encounter_model;

            std::vector<domain::enemy> enemies;
            std::vector<domain::player> players;

            for (auto& enemy_model : encounter_model.enemies)
            {
                if(std::strlen(enemy_model.name) > 0)
                    enemies.emplace_back(enemy_model.id, enemy_model.name, enemy_model.health);
            }

            for(auto& player_model : encounter_model.players)
            {
                if(std::strlen(player_model.name) > 0)
                    players.emplace_back(player_model.id, player_model.name, player_model.health);
            }

            const domain::encounter encounter(enemies, players);               
            if(get_encounter_callback != nullptr)
            {
                get_encounter_callback(encounter);
                get_encounter_callback = nullptr;
                return true;
            }

            return false;
        }
    default:
        return false;
    }
}
