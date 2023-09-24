﻿#include "client.h"

#include "Domain/action.h"
#include "Domain/action_log.h"
#include "Domain/player_class.h"
#include "Domain/player_complete.h"
#include "Models/action_use_model.h"
#include "Models/create_player_model.h"
#include "Models/encounter_model.h"
#include "Models/player_classes_model.h"
#include "Models/player_config_model.h"
#include "Models/simple_answer_model.h"
using namespace dungeon_common;
using namespace dungeon_client;

std::string player_input;
std::thread input_thread;

void read_input_thread(std::string& input)
{
    while (true)
    {
        std::string x;
        std::getline(std::cin, x);
        input = x;
    }
}

client::client()
{
    input_thread = std::thread(read_input_thread, std::ref(player_input));
}

void client::end() const
{
    input_thread.join();
}

void client::connect(const std::string& host, const uint16_t port, const std::function<void(dungeon_common::model::simple_answer_model)>& callback)
{
    base_client::connect(host, port);
    connection_callback = callback;
    wait_message();
}

void client::validate_name(const char* name, const std::function<void(model::simple_answer_model)>& callback)
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

void client::get_player_classes(const std::function<void(std::vector<domain::player_class> player_classes)>& callback)
{
    const message<custom_msg_types> msg(custom_msg_types::get_player_classes);

    get_player_classes_callback = callback;
    send(msg);
    wait_message();
}

void client::create_player(const std::string& name, const enums::player_class_type player_class, const std::function<void(domain::player_complete)>& callback)
{
    const model::create_player_model model(name, player_class);
    message<custom_msg_types> msg(custom_msg_types::create_player);
    msg << model;

    create_player_callback = callback;
    send(msg);
    wait_message();
}

void client::set_player(domain::player_complete& player)
{
    player_ptr_ = std::make_unique<domain::player_complete>(player);
}

void client::set_player_ready(const bool ready, const std::function<void(domain::lobby)>& callback)
{
    message<custom_msg_types> msg(custom_msg_types::player_ready);
    msg << ready;

    set_player_ready_callback = callback;
    send(msg);
    wait_message();
}

void client::send_action(const model::action_types action_id, const std::string& target_id)
{
    const model::action_use_model action(action_id, player_ptr_->public_id, target_id);
    message<custom_msg_types> msg(custom_msg_types::player_action);

    msg << action;
    send(msg);
    wait_message();
}

void client::request_match_start(const std::function<void(domain::encounter)>& callback)
{
    get_encounter_callback = callback;
    const message<custom_msg_types> msg(custom_msg_types::match_start_request);
    send(msg);
    wait_message();
}

domain::player_complete client::get_player() const
{
    return *player_ptr_;
}

void client::read_input(const std::function<void(std::string input)>& callback)
{
    player_input.clear();
    player_input_callback = callback;
    std::cout << "> ";

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
    case custom_msg_types::get_player_classes_response:
        {
            model::player_classes_model response;
            msg >> response;

            std::vector<domain::player_class> player_classes;
            std::ranges::for_each(response.classes, [&player_classes](auto player_class_model)
            {
                player_classes.emplace_back(player_class_model.id, player_class_model.name);
            });

            if (get_player_classes_callback != nullptr)
            {
                get_player_classes_callback(player_classes);
                get_player_classes_callback = nullptr;
                return true;
            }

            return false;
        }
    case custom_msg_types::create_player:
        {
            model::player_config_model response;
            msg >> response;

            std::array<domain::action, 4> actions;
            for (size_t i = 0; i < actions.max_size(); ++i)
            {
                domain::action action(response.actions[i].id, response.actions[i].name, response.actions[i].targets_count);
                actions[i] = action;
            }

            domain::player_class player_class(response.player_class.id, response.player_class.name);
            domain::player_complete player_complete(response.id, response.name, player_class, response.attack_damage, response.ability_power,
                                                    response.health, response.max_health, actions);

            if (create_player_callback != nullptr)
            {
                create_player_callback(player_complete);
                create_player_callback = nullptr;
                return true;
            }
            return false;
        }
    case custom_msg_types::player_ready_response:
        {
            model::lobby_model response;
            msg >> response;
            const domain::lobby lobby(response);

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
            model::simple_answer_model response;
            msg >> response;
            return false;
        }
    case custom_msg_types::encounter_update_response:
        {
            model::encounter_model encounter_model;
            msg >> encounter_model;

            std::vector<domain::enemy> enemies;
            std::vector<domain::player> players;

            for (auto& enemy_model : encounter_model.enemies)
            {
                if (std::strlen(enemy_model.id) > 0)
                    enemies.emplace_back(enemy_model.id, enemy_model.name, enemy_model.health, enemy_model.max_health);
            }

            for (auto& player_model : encounter_model.players)
            {
                if (std::strlen(player_model.name) > 0)
                {
                    domain::player_class player_class(player_model.player_class.id, player_model.player_class.name);
                    players.emplace_back(player_model.id, player_model.name, player_class, player_model.health, player_model.max_health);
                }
            }

            std::list<std::string> action_log;
            for(auto& log_model : encounter_model.log)
            {
                if(log_model[0] == '\0')
                    continue;
                
                std::string log(log_model);
                action_log.push_back(log);
            }

            domain::encounter encounter(enemies, players, encounter_model.active_creature_id, action_log,
                                        encounter_model.game_over, encounter_model.players_won);
            if (get_encounter_callback != nullptr)
            {
                get_encounter_callback(std::move(encounter));
                return true;
            }

            return false;
        }
    default:
        return false;
    }
}
