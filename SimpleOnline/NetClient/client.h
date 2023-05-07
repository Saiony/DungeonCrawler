#pragma once
#include<dungeon_network.h>

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
        void init();
        void end() const;
        void connect(const string& host, const uint16_t port, const function<void(dungeon_common::model::simple_answer_model)>& callback);
        void validate_name(const char* name, const function<void(dungeon_common::model::simple_answer_model)>& callback);
        void create_player(const char* name, const function<void(dungeon_common::model::player_model)>& callback);
        void set_player(domain::player& player);
        void set_player_ready(const bool ready, const function<void(domain::lobby_domain)>& callback);
        void send_action(action_types action_id, int target_id);
        void send_action(action_types action_id, int target_id) const;
        void read_input(const function<void(string input)>& callback);

        function<void(string input)> player_input_callback;
        function<void(dungeon_common::model::simple_answer_model)> validate_name_callback;
        function<void(dungeon_common::model::player_model)> create_player_callback;
        function<void(domain::lobby_domain)> set_player_ready_callback;
        function<void(dungeon_common::model::simple_answer_model)> connection_callback;
    };
}
