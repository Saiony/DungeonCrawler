#pragma once
#include<dungeon_network.h>

#include "Domain/encounter.h"
#include "Domain/lobby.h"
#include "Domain/player_complete.h"
#include "Models/action_use_model.h"
#include "Models/player_config_model.h"
#include "Models/simple_answer_model.h"

namespace dungeon_client
{
    class client : public dungeon_common::base_client<dungeon_common::custom_msg_types>
    {
    private:
        std::unique_ptr<domain::player_complete> player_ptr_;
        bool handle_messages();
    public:
        std::condition_variable condition_var;        
        std::mutex mutex;

        client();
        void end() const;
        void connect(const std::string& host, const uint16_t port, const std::function<void(dungeon_common::model::simple_answer_model)>& callback);
        void read_input(const std::function<void(std::string input)>& callback);
        void validate_name(const char* name, const std::function<void(dungeon_common::model::simple_answer_model)>& callback);
        void create_player(const char* name, const std::function<void(domain::player_complete)>& callback);
        void set_player(domain::player_complete& player);
        void set_player_ready(const bool ready, const std::function<void(domain::lobby)>& callback);
        void send_action(const dungeon_common::model::action_types action_id, const std::string& target_id);
        void request_match_start(const std::function<void(domain::encounter)>& callback);
        void wait_message();
        domain::player_complete get_player() const;

        std::function<void(std::string input)> player_input_callback;
        std::function<void(dungeon_common::model::simple_answer_model)> connection_callback;
        std::function<void(dungeon_common::model::simple_answer_model)> validate_name_callback;
        std::function<void(domain::player_complete)> create_player_callback;
        std::function<void(domain::lobby)> set_player_ready_callback;
        std::function<void(domain::encounter)> get_encounter_callback;
    };
}
