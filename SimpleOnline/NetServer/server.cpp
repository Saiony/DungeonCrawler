#include "server.h"
#include<string>

#include "Models/player_model.h"
#include "Models/simple_answer_model.h"
using namespace dungeon_server;

server::server(const uint16_t n_port) : base_server<custom_msg_types>(n_port)
{
    const domain::player debug_player(5, "saiony", 50);
    players_.push_back(debug_player);
}

bool server::can_client_connect(shared_ptr<connection<custom_msg_types>> client)
{
    return true;
}

void server::on_client_connect(shared_ptr<connection<custom_msg_types>> client)
{
    message<custom_msg_types> msg;
    msg.header.id = custom_msg_types::server_accept;
    client->send(msg);
}

void server::on_client_disconnect(shared_ptr<connection<custom_msg_types>> client)
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
            break;
        }
    case custom_msg_types::validate_name:
        {
            const auto player_name = msg.read_body().substr(0, msg.read_body().find('\0', 0));            
            cout << "Validating name from player: " << player_name << endl;

            error_code_type error_code = {};
            const auto valid = none_of(begin(players_), end(players_), [player_name](const domain::player& player){ return player.name == player_name; });
            error_code = valid ? error_code_type::none : error_code_type::name_already_taken;         

            //answer
            message<custom_msg_types> answer;
            answer.header.id = custom_msg_types::validate_name;
            const simple_answer_model body(valid, error_code);
            answer << body;
            
            message_client(client->get_id(), answer);            
            break;
        }
    default:
        cout << "Invalid MsgType";
        break;
    }
}
