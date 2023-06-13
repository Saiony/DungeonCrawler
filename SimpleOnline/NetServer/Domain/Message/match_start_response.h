#pragma once
#include "emitter_message.h"
#include "NetServer/Domain/Player.h"

namespace dungeon_server::domain::message
{
    class match_start_response final : public emitter_message
    {
    public:
        std::shared_ptr<player> player;
        std::shared_ptr<encounter> encounter;
        
        explicit match_start_response(std::shared_ptr<domain::player> player, std::shared_ptr<domain::encounter> encounter) : player(std::move(player)), encounter(std::move(encounter))
        {
        }
    
        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::match_start_response;
        }
    };
}