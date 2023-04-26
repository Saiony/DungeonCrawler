#pragma once
#include<dungeon_network.h>

#include "Domain/lobby_domain.h"
#include "Domain/Player.h"
#include "Models/player_model.h"
#include "Models/simple_answer_model.h"

namespace dungeon_client
{
    class client : public dungeon_common::base_client<dungeon_common::custom_msg_types>
    {
    private:
        domain::player player_ = {};
    public:
        std::condition_variable message_cv;
        std::condition_variable condition_var;        
        std::mutex mutex;
        
        void validate_name(const char* name);
        void create_player(const char* name);
        void set_player(domain::player& player);
        void set_player_ready(const bool ready, const function<void(domain::lobby_domain)>& callback);

        // function<void(simple_answer_model)> validate_name_callback;
        // function<void(dungeon_common::model::player_model)> create_player_callback;
        function<void(domain::lobby_domain)> set_player_ready_callback;

        dungeon_common::model::simple_answer_model server_connection_response;
        dungeon_common::model::simple_answer_model validate_name_response;
        dungeon_common::model::player_model create_player_response;
        domain::lobby_domain set_player_ready_response;
    };
}
