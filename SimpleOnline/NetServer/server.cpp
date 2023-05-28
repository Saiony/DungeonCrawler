#include "server.h"
#include<string>

#include "Domain/Encounter.h"
#include "Domain/Enemies/Wolf.h"
#include "Domain/Factory/action_factory.h"
#include "Models/action_model.h"
#include "Models/encounter_model.h"
#include "Models/lobby_model.h"
#include "Models/player_model.h"
#include "Models/simple_answer_model.h"
using namespace dungeon_server;

server::server(const uint16_t n_port) : base_server<custom_msg_types>(n_port)
{
}

bool server::can_client_connect(const std::shared_ptr<connection<custom_msg_types>>& connection)
{
    return connections_.size() < max_players_;
}

void server::on_client_connect(const std::shared_ptr<connection<custom_msg_types>>& client)
{
    message<custom_msg_types> msg(custom_msg_types::server_connection_response);
    model::simple_answer_model answer;
    
    if (!can_client_connect(client))
    {
        std::cout << "[-----] Server is full, connection denied" << std::endl;
        answer.ok = false;
        answer.error_code = error_code_type::server_full;
    }
    else
    {
        std::cout << "[" << client->get_id() << "] Connection Approved\n";
        answer.ok = true;
        answer.error_code = error_code_type::none;
    }
    
    msg << answer;
    client->send(msg);
}

void server::on_client_disconnect(const std::shared_ptr<connection<custom_msg_types>> client)
{
    std::cout << "Removing client [" << client->get_id() << "]\n";
}

void server::on_message(const std::shared_ptr<connection<custom_msg_types>> client, message<custom_msg_types>& msg)
{
    switch (msg.header.id)
    {
    case custom_msg_types::create_player:
        {
            const auto player_name = msg.read_body().substr(0, msg.read_body().find('\0', 0));

            //create player domain and add to the list
            const domain::player player_domain(client->get_id(), player_name, 37);
            players_.push_back(player_domain);

            //add player to lobby domain
            const auto player_lobby = domain::lobby::player_lobby_domain(player_domain.private_id, player_domain.name, false);
            lobby_.players_ready.push_back(player_lobby);
            
            //create player model and send to client
            const model::player_model player_model(player_domain.public_id, player_name, 37);
            message<custom_msg_types> answer(custom_msg_types::create_player);
            answer << player_model;
            message_client(client->get_id(), answer);

            break;
        }
    case custom_msg_types::validate_name:
        {
            const auto player_name = msg.read_body().substr(0, msg.read_body().find('\0', 0));

            error_code_type error_code = {};
            const auto valid = std::ranges::none_of(players_, [player_name](const domain::player& player)
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
            const auto player_lobby = std::ranges::find_if(lobby_.players_ready,
                                                                      [client](const domain::lobby::player_lobby_domain& player_ready)
                                                                      {
                                                                          return player_ready.get_private_id() == client->get_id();
                                                                      });
            player_lobby->set_ready(ready);

            //answer
            model::lobby_model lobby_model;
            for (size_t i = 0; i < lobby_.players_ready.size(); i++)
            {
                strcpy_s(lobby_model.players_lobby_status[i].name, lobby_.players_ready[i].get_name());
                lobby_model.players_lobby_status[i].ready = lobby_.players_ready[i].get_ready();
            }
            lobby_model.start_match = lobby_.start_match();

            message<custom_msg_types> answer(custom_msg_types::player_ready_response);
            answer << lobby_model;
            broadcast_message(answer);

            break;
        }
    case custom_msg_types::match_start_request:
        {         
            const domain::enemy::wolf wolf("wolf", 10, 15);
            std::vector<domain::enemy::base_enemy> enemies = { static_cast<domain::enemy::base_enemy>(wolf) };
            domain::encounter::encounter encounter(enemies);

            model::encounter_model encounter_model;
            for(size_t i = 0; i < enemies.size(); i++)
            {
                encounter_model.enemies[i] = model::enemy_model(enemies[i].get_id(), enemies[i].get_name(), enemies[i].get_health());
            }

            for(size_t i = 0; i < players_.size(); i++)
            {
                encounter_model.players[i] = model::player_model(players_[i].public_id, players_[i].name, players_[i].health);    
            }

            message<custom_msg_types> answer(custom_msg_types::match_start_response);
            answer << encounter_model;
            message_client(client->get_id(), answer);
            
            break;
        }
    case custom_msg_types::player_action:
        {
            action_model action_model;
            msg >> action_model;

            auto action = ::domain::action::action_factory::create_action(action_model);
            action->use();
            break;
        }
    default:
        std::cout << "Invalid MsgType"; 
        break;
    }
}
