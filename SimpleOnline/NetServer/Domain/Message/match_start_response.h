#pragma once
#include "emitter_message.h"
#include "Models/encounter_model.h"
#include "NetServer/Domain/Player.h"

namespace dungeon_server::domain::message
{
    class match_start_response : public emitter_message
    {
    public:
        player player;
        encounter encounter;
        
        explicit match_start_response(domain::player player, domain::encounter encounter) : player(std::move(player)), encounter(std::move(encounter))
        {
        }
    
        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::match_start_response;
        }
    };
}