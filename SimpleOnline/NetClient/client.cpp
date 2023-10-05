#include "client.h"

#include "bonfire_story_model.h"
#include "bonfire_result_model.h"
#include "bonfire_story_teller_model.h"
#include "gameplay_state_model.h"
#include "story_model.h"
#include "story_read_model.h"
#include "Domain/action.h"
#include "Domain/action_log.h"
#include "Domain/bonfire_result.h"
#include "Domain/bonfire_story_telling.h"
#include "Domain/gameplay_state.h"
#include "Domain/player_class.h"
#include "Domain/player_complete.h"
#include "Domain/story.h"
#include "Domain/story_read.h"
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

void client::request_next_state(const std::function<void(domain::gameplay_state)>& callback)
{
    get_gameplay_state_callback = callback;
    const message<custom_msg_types> msg(custom_msg_types::get_gameplay_state);
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

void client::request_story(const std::function<void(domain::story)>& callback)
{
    get_story_callback = callback;
    const message<custom_msg_types> msg(custom_msg_types::story_request);
    send(msg);
    wait_message();
}

void client::send_story_read(const std::function<void(domain::story_read)>& callback)
{
    send_story_read_callback = callback;
    const message<custom_msg_types> msg(custom_msg_types::confirm_story_read);
    send(msg);
    wait_message();
}

void client::request_bonfire_story_teller(const std::function<void(domain::bonfire_story_telling)>& callback)
{
    get_bonfire_story_teller_callback = callback;
    const message<custom_msg_types> msg(custom_msg_types::bonfire_story_teller_request);
    send(msg);
    wait_message();
}

void client::send_bonfire_story(const domain::creature_stats& stat, const std::string& story,
                                const std::function<void(domain::bonfire_result)>& callback)
{
    subscribe_bonfire_result(callback);
    
    const model::bonfire_story_model model(stat.id, story);
    message<custom_msg_types> msg(custom_msg_types::bonfire_story);
    msg << model;

    send(msg);
    wait_message();
}

void client::subscribe_bonfire_result(const std::function<void(domain::bonfire_result)>& callback)
{
    bonfire_story_result_callback = callback;
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
    case custom_msg_types::gameplay_state_response:
        {
            model::gameplay_state_model response;
            msg >> response;

            domain::gameplay_state state(response.state);

            if (get_gameplay_state_callback != nullptr)
            {
                get_gameplay_state_callback(state);
                get_gameplay_state_callback = nullptr;
                return true;
            }

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
            for (auto& log_model : encounter_model.log)
            {
                if (log_model[0] == '\0')
                    continue;

                std::string log(log_model);
                action_log.push_back(log);
            }

            domain::encounter encounter(enemies, players, encounter_model.active_creature_id, action_log,
                                        encounter_model.combat_ended);
            if (get_encounter_callback != nullptr)
            {
                get_encounter_callback(encounter);
                return true;
            }

            return false;
        }
    case custom_msg_types::story_response:
        {
            model::story_model story_model;
            msg >> story_model;

            std::list<std::string> stories;
            for (auto& story_log_model : story_model.story)
            {
                if (story_log_model[0] == '\0')
                    continue;

                std::string log(story_log_model);
                stories.push_back(log);
            }

            domain::story story(stories);

            if (get_story_callback != nullptr)
            {
                get_story_callback(story);
                get_story_callback = nullptr;
                return true;
            }

            return false;
        }
    case custom_msg_types::story_read_response:
        {
            model::story_read_model story_read_model;
            msg >> story_read_model;

            domain::story_read story_read(story_read_model.everyone_read);

            if (send_story_read_callback != nullptr)
            {
                send_story_read_callback(story_read);
                return true;
            }

            return false;
        }
    case custom_msg_types::bonfire_story_teller_response:
        {
            model::bonfire_story_teller_model model;
            msg >> model;

            auto story_teller_model = model.story_teller;
            domain::player_class player_class(story_teller_model.player_class.id, story_teller_model.player_class.name);
            domain::player story_teller(story_teller_model.id, story_teller_model.name, player_class,
                                        story_teller_model.health, story_teller_model.max_health);

            std::vector<domain::creature_stats> player_stats;
            std::ranges::for_each(model.player_stats, [&player_stats](auto stats)
            {
                player_stats.emplace_back(stats.id, stats.name);
            });

            domain::bonfire_story_telling story_telling(story_teller, model.max_characters, player_stats);

            if (get_bonfire_story_teller_callback != nullptr)
            {
                get_bonfire_story_teller_callback(story_telling);
                return true;
            }

            return false;
        }
    case custom_msg_types::bonfire_result_response:
        {
            model::bonfire_result_model model;
            msg >> model;

            domain::creature_stats upgraded_stat(model.upgraded_stat.id, model.upgraded_stat.name);
            auto story_teller_model = model.story_teller;
            domain::player_class player_class(story_teller_model.player_class.id, story_teller_model.player_class.name);
            domain::player story_teller(story_teller_model.id, story_teller_model.name, player_class,
                                        story_teller_model.health, story_teller_model.max_health);

            std::list<std::string> story_log;
            for (auto& log_model : model.level_up_log)
            {
                if (log_model[0] == '\0')
                    continue;

                std::string log(log_model);
                story_log.push_back(log);
            }


            domain::bonfire_result bonfire_result(story_teller, upgraded_stat, story_log, model.story);

            if (bonfire_story_result_callback != nullptr)
            {
                bonfire_story_result_callback(bonfire_result);
                return true;
            }

            return false;
        }
    default:
        return false;
    }
}
