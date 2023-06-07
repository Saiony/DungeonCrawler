#pragma once
#include "emitter_message.h"
#include "NetServer/Domain/Player.h"

class match_start_response : public emitter_message
{
public:
    dungeon_server::domain::player player;

    explicit match_start_response(dungeon_server::domain::player player) : player(std::move(player))
    {        
    }
    
    dungeon_common::custom_msg_types get_id() override
    {
        return dungeon_common::custom_msg_types::match_start_response;
    }
};
