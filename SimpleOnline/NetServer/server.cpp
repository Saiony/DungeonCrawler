#include <memory>
#include<string>
#include "server.h"
#include "Domain/Encounter.h"
#include "Domain/player_classes.h"
#include "Domain/Enemies/Wolf.h"
#include "Domain/Factory/action_factory.h"
#include "Domain/Factory/player_factory.h"
#include "Domain/Message/emitter_message.h"
#include "Domain/Message/encounter_update_response.h"
#include "Domain/Message/match_start_response.h"
#include "Models/action_use_model.h"
#include "Models/create_player_model.h"
#include "Models/encounter_model.h"
#include "Models/lobby_model.h"
#include "Models/player_classes_model.h"
#include "Models/player_config_model.h"
#include "Models/player_model.h"
#include "Models/simple_answer_model.h"

using namespace dungeon_server;

server::server(const uint16_t n_port) : base_server<dungeon_common::custom_msg_types>(n_port)
{
}

bool server::can_client_connect(const std::shared_ptr<dungeon_common::connection<dungeon_common::custom_msg_types>>& connection)
{
    return connections_.size() < max_players_;
}

void server::on_client_connect(const std::shared_ptr<dungeon_common::connection<dungeon_common::custom_msg_types>>& client)
{
    dungeon_common::message<dungeon_common::custom_msg_types> msg(dungeon_common::custom_msg_types::server_connection_response);
    dungeon_common::model::simple_answer_model answer;

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

void server::on_client_disconnect(const std::shared_ptr<dungeon_common::connection<dungeon_common::custom_msg_types>> client)
{
    std::cout << "Removing client [" << client->get_id() << "]\n";
    connections_.erase(std::ranges::remove(connections_, client).begin(), connections_.end());
}

void server::update(const size_t max_messages, const bool wait)
{
    base_server<dungeon_common::custom_msg_types>::update(max_messages, wait);

    if (game_room_ptr_ != nullptr)
        game_room_ptr_->update();
}

void server::on_game_room_message(const std::shared_ptr<domain::message::emitter_message>& emitter_msg)
{
    switch (emitter_msg->get_id())
    {
    case dungeon_common::custom_msg_types::match_start_response:
        {
            const auto match_start_msg_ptr = std::dynamic_pointer_cast<domain::message::match_start_response>(emitter_msg);
            const auto encounter = match_start_msg_ptr->encounter;
            dungeon_common::model::encounter_model encounter_model;

            for (size_t i = 0; i < encounter->enemies.size(); i++)
            {
                const auto enemy = encounter->enemies[i];
                encounter_model.enemies[i] = dungeon_common::model::enemy_model(enemy->public_id, enemy->name, enemy->health, enemy->max_health);
            }
            for (size_t i = 0; i < encounter->players.size(); i++)
            {
                const auto player_ptr = encounter->players[i];
                dungeon_common::model::player_class_model player_class_model(player_ptr->player_class.id, player_ptr->player_class.name);
                encounter_model.players[i] = dungeon_common::model::player_model(player_ptr->public_id, player_ptr->name, player_class_model,
                                                                                 player_ptr->health, player_ptr->max_health);
            }

            std::ranges::copy(encounter->active_creature->public_id, encounter_model.active_creature_id);
            encounter_model.game_over = false;
            encounter_model.players_won = false;
            dungeon_common::message<dungeon_common::custom_msg_types> answer(dungeon_common::custom_msg_types::encounter_update_response);
            answer << encounter_model;
            message_client(match_start_msg_ptr->player->private_id, answer);
            break;
        }
    case dungeon_common::custom_msg_types::encounter_update_response:
        {
            std::cout << "\nENCOUNTER UPDATE MSG";
            const auto encounter_update = std::dynamic_pointer_cast<domain::message::encounter_update_response>(emitter_msg);
            const auto encounter = encounter_update->encounter_ptr;
            dungeon_common::model::encounter_model encounter_model;

            for (size_t i = 0; i < encounter->enemies.size(); i++)
            {
                const auto enemy_ptr = encounter->enemies[i];
                encounter_model.enemies[i] = dungeon_common::model::enemy_model(enemy_ptr->public_id, enemy_ptr->name,
                                                                                enemy_ptr->health, enemy_ptr->max_health);
            }
            for (size_t i = 0; i < encounter->players.size(); i++)
            {
                const auto player_ptr = encounter->players[i];
                dungeon_common::model::player_class_model player_class_model(player_ptr->player_class.id, player_ptr->player_class.name);
                encounter_model.players[i] = dungeon_common::model::player_model(player_ptr->public_id, player_ptr->name,
                                                                                 player_class_model, player_ptr->health,
                                                                                 player_ptr->max_health);
            }

            std::ranges::copy(encounter->active_creature->public_id, encounter_model.active_creature_id);
            std::ranges::copy(encounter_update->log, encounter_model.log);

            encounter_model.game_over = encounter->game_over;
            encounter_model.players_won = encounter->players_won;

            dungeon_common::message<dungeon_common::custom_msg_types> answer(dungeon_common::custom_msg_types::encounter_update_response);
            answer << encounter_model;
            broadcast_message(answer);

            std::cout << "\nENCOUNTER UPDATE MSG SENT";

            if (encounter->game_over)
                running = false;

            break;
        }
    default: break;
    }
}

void server::on_message(const std::shared_ptr<dungeon_common::connection<dungeon_common::custom_msg_types>> client,
                        dungeon_common::message<dungeon_common::custom_msg_types>& msg)
{
    switch (msg.header.id)
    {
    case dungeon_common::custom_msg_types::create_player:
        {
            dungeon_common::model::create_player_model model;
            msg >> model;

            //create player domain and add to the list
            auto player = domain::factory::player_factory::create_player(client->get_id(), model.name, model.player_class_type);
            players_.push_back(player);

            //add player to lobby domain
            const auto player_lobby = domain::lobby::player_lobby_domain(player->private_id, player->name, player->player_class, false);
            lobby_.players_ready.push_back(player_lobby);

            //create models
            std::vector<player_action_model> player_actions;
            std::ranges::for_each(player->actions, [&player_actions, &player](auto action)
            {
                auto action_domain = domain::factory::action_factory::create_action(action, player->public_id);
                const player_action_model action_model(action, action_domain->get_name(), action_domain->get_targets_count());
                player_actions.push_back(action_model);
            });
            dungeon_common::model::player_class_model player_class_model(player->player_class.id, player->player_class.name);

            const dungeon_common::model::player_config_model player_model(player->public_id, player->name, player_class_model, player->health, player->max_health,
                                                                          player->get_attack_damage(), player->get_ability_power(), player_actions);
            dungeon_common::message<dungeon_common::custom_msg_types> answer(dungeon_common::custom_msg_types::create_player);
            answer << player_model;
            message_client(client->get_id(), answer);

            break;
        }
    case dungeon_common::custom_msg_types::validate_name:
        {
            const auto player_name = msg.read_body().substr(0, msg.read_body().find('\0', 0));

            error_code_type error_code = {};
            const auto valid = std::ranges::none_of(players_, [player_name](const std::shared_ptr<domain::player>& player)
            {
                return player->name == player_name;
            });
            error_code = valid ? error_code_type::none : error_code_type::name_already_taken;

            //answer
            dungeon_common::message<dungeon_common::custom_msg_types> answer(dungeon_common::custom_msg_types::validate_name);
            const dungeon_common::model::simple_answer_model body(valid, error_code);
            answer << body;

            message_client(client->get_id(), answer);
            break;
        }
    case dungeon_common::custom_msg_types::get_player_classes:
        {
            dungeon_common::model::player_classes_model model;
            domain::player_classes player_classes;

            auto classes = player_classes.classes;
            for (int i = 0; i < std::size(classes); i++)
            {
                dungeon_common::model::player_class_model player_class_model(classes[i].id, classes[i].name);
                model.classes[i] = player_class_model;
            }

            //answer
            dungeon_common::message<dungeon_common::custom_msg_types> answer(dungeon_common::custom_msg_types::get_player_classes_response);
            answer << model;
            message_client(client->get_id(), answer);
            break;
        }
    case dungeon_common::custom_msg_types::player_ready:
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
            dungeon_common::model::lobby_model lobby_model;
            for (size_t i = 0; i < lobby_.players_ready.size(); i++)
            {
                strcpy_s(lobby_model.players_lobby_status[i].name, lobby_.players_ready[i].get_name());
                lobby_model.players_lobby_status[i].player_class = dungeon_common::model::player_class_model(lobby_.players_ready[i].get_player_class().id,
                                                                                                             lobby_.players_ready[i].get_player_class().name);
                lobby_model.players_lobby_status[i].ready = lobby_.players_ready[i].get_ready();
            }
            lobby_model.start_match = lobby_.can_start_match();

            dungeon_common::message<dungeon_common::custom_msg_types> answer(dungeon_common::custom_msg_types::player_ready_response);
            answer << lobby_model;
            broadcast_message(answer);

            //create game room
            if (!lobby_model.start_match)
                return;

            game_room_ptr_ = std::make_unique<game_room::game_room>(players_,
                            [this](const std::shared_ptr<domain::message::emitter_message>& emitter_msg)
                            {
                                on_game_room_message(emitter_msg);
                            });
            break;
        }
    case dungeon_common::custom_msg_types::match_start_request:
        {
            auto player = *std::ranges::find_if(players_, [&client](auto p)
            {
                return p->private_id == client->get_id();
            });
            game_room_ptr_->player_match_start_request(player);

            break;
        }
    case dungeon_common::custom_msg_types::player_action:
        {
            dungeon_common::model::action_use_model action_use_model;
            msg >> action_use_model;
            auto action = ::domain::factory::action_factory::create_action(action_use_model);
            game_room_ptr_->handle_player_input(action);

            break;
        }
    default:
        std::cout << "Invalid MsgType";
        break;
    }
}
