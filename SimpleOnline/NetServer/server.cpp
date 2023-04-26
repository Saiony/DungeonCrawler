#include "server.h"
#include<string>

#include "Models/lobby_model.h"
#include "Models/player_model.h"
#include "Models/simple_answer_model.h"
using namespace dungeon_server;

server::server(const uint16_t n_port) : base_server<custom_msg_types>(n_port)
{
    const domain::player debug_player(5, "saiony", 50);
    players_.push_back(debug_player);
}

bool server::can_client_connect(const shared_ptr<connection<custom_msg_types>>& connection)
{
    return connections_.size() < max_players_;
}

void server::on_client_connect(const shared_ptr<connection<custom_msg_types>>& client)
{
    message<custom_msg_types> msg(custom_msg_types::server_connection_response);
    model::simple_answer_model answer;
    
    if (!can_client_connect(client))
    {
        cout << "[-----] Server is full, connection denied" << endl;
        answer.ok = false;
        answer.error_code = error_code_type::server_full;
    }
    else
    {
        cout << "[" << client->get_id() << "] Connection Approved\n";
        answer.ok = true;
        answer.error_code = none;
    }
    
    msg << answer;
    client->send(msg);
}

void server::on_client_disconnect(const shared_ptr<connection<custom_msg_types>> client)
{
    cout << "Removing client [" << client->get_id() << "]\n";
}

void server::on_message(const shared_ptr<connection<custom_msg_types>> client, message<custom_msg_types>& msg)
{
    switch (msg.header.id)
    {
    case custom_msg_types::create_player:
        {
            const auto player_name = msg.read_body().substr(0, msg.read_body().find('\0', 0));

            //create player model and send to client
            const model::player_model player_model(client->get_id(), player_name, 37);
            message<custom_msg_types> answer(custom_msg_types::create_player);
            answer << player_model;
            message_client(client->get_id(), answer);

            //create player domain and add to the list
            const domain::player player_domain(player_model.id_, player_name, player_model.health_);
            players_.push_back(player_domain);

            const auto player_lobby = domain::lobby::player_lobby_domain(
                player_domain.private_id, player_domain.name, false);
            players_ready_.push_back(player_lobby);
            break;
        }
    case custom_msg_types::validate_name:
        {
            const auto player_name = msg.read_body().substr(0, msg.read_body().find('\0', 0));

            error_code_type error_code = {};
            const auto valid = ranges::none_of(players_, [player_name](const domain::player& player)
            {
                return player.name == player_name;
            });
            error_code = valid ? error_code_type::none : error_code_type::name_already_taken;

            //answer
            message<custom_msg_types> answer(custom_msg_types::validate_name);
            const model::simple_answer_model body(valid, error_code);
            answer << body;

            message_client(client->get_id(), answer);
            break;
        }
    case custom_msg_types::player_ready:
        {
            bool ready;
            msg >> ready;

            //update lobby domain
            const auto player_lobby_status = ranges::find_if(players_ready_,[client](
                 const domain::lobby::player_lobby_domain& player_ready)
                 {
                     return player_ready.get_id() == client->get_id();
                 });
            player_lobby_status->set_ready(ready);

            //answer
            model::lobby_model player_lobby;
            for (size_t i = 0; i < players_ready_.size(); i++)
            {
                strcpy_s(player_lobby.players_lobby_status[i].name_, players_ready_[i].get_name());
                player_lobby.players_lobby_status[i].ready_ = players_ready_[i].get_ready();
            }

            message<custom_msg_types> answer(custom_msg_types::player_ready_response);
            answer << player_lobby;

            broadcast_message(answer);

            break;
        }
    default:
        cout << "Invalid MsgType";
        break;
    }
}
