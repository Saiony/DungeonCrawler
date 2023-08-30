#pragma once
#include "emitter_message.h"
#include "NetServer/Domain/Encounter.h"

namespace dungeon_server::domain::message
{
    class encounter_update_response : public emitter_message
    {
    public:
        std::shared_ptr<encounter> encounter_ptr;
        std::string log;
        
        explicit encounter_update_response(std::shared_ptr<encounter> encounter_ptr, std::string action_log)
                                           : encounter_ptr(std::move(encounter_ptr)), log(std::move(action_log))
        {
        }

        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::encounter_update_response;
        }
    };
}
