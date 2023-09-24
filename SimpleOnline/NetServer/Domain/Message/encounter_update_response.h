#pragma once
#include "emitter_message.h"
#include "NetServer/Domain/action_log.h"
#include "NetServer/Domain/Encounter.h"

namespace dungeon_server::domain::message
{
    class encounter_update_response final : public emitter_message
    {
    public:
        std::shared_ptr<encounter> encounter_ptr;
        action_log log;
        
        explicit encounter_update_response(std::shared_ptr<encounter> encounter_ptr, action_log log)
                                           : encounter_ptr(std::move(encounter_ptr)), log(std::move(log))
        {
        }

        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::encounter_update_response;
        }
    };
}
