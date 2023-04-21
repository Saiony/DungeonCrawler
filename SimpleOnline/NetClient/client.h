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
        void validate_name(const char* name, const function<void(simple_answer_model)>& callback);
        void create_player(const char* name, const function<void(dungeon_common::model::player_model)>& callback);
        void set_player(domain::player& player);
        void set_player_ready(bool ready, const function<void(domain::lobby_domain)>& callback);
    
        function<void(simple_answer_model)> validate_name_callback;
        function<void(dungeon_common::model::player_model)> create_player_callback;
        function<void(domain::lobby_domain)> set_player_ready_callback;
    };
}
