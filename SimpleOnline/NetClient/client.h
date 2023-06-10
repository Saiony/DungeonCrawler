#pragma once
#include<dungeon_network.h>

#include "Domain/encounter.h"
#include "Domain/lobby_domain.h"
#include "Domain/Player.h"
#include "Models/action_model.h"
#include "Models/player_model.h"
#include "Models/simple_answer_model.h"

namespace dungeon_client
{
    class client : public dungeon_common::base_client<dungeon_common::custom_msg_types>
    {
    private:
        domain::player player_ = {};
        bool handle_messages();
        void wait_message();
    public:
        std::condition_variable condition_var;        
        std::mutex mutex;

        client();
        void end() const;
        void connect(const std::string& host, const uint16_t port, const std::function<void(dungeon_common::model::simple_answer_model)>& callback);
        void read_input(const std::function<void(std::string input)>& callback);
        void validate_name(const char* name, const std::function<void(dungeon_common::model::simple_answer_model)>& callback);
        void create_player(const char* name, const std::function<void(dungeon_common::model::player_model)>& callback);
        void set_player(domain::player& player);
        void set_player_ready(const bool ready, const std::function<void(domain::lobby_domain)>& callback);
        void send_action(const dungeon_common::model::action_types action_id, const std::string& target_id);
        void request_match_start(const std::function<void(domain::encounter)>& callback);

        std::function<void(std::string input)> player_input_callback;
        std::function<void(dungeon_common::model::simple_answer_model)> connection_callback;
        std::function<void(dungeon_common::model::simple_answer_model)> validate_name_callback;
        std::function<void(dungeon_common::model::player_model)> create_player_callback;
        std::function<void(domain::lobby_domain)> set_player_ready_callback;
        std::function<void(domain::encounter)> get_encounter_callback;
    };
}
