#pragma once
#include<dungeon_network.h>

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
        void consult_spell(const char* spell);
        void validate_name(const char* name, function<void(simple_answer_model)> callback);
        void create_player(const char*name, function<void(dungeon_common::model::player_model)> callback);
        void set_player(domain::player& player);
    
        function<void(simple_answer_model)> validate_name_callback;
        function<void(dungeon_common::model::player_model)> create_player_callback;
    };
}
