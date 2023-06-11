#pragma once
#include "emitter_message.h"
#include "NetServer/Domain/Encounter.h"

namespace dungeon_server::domain::message
{
    class encounter_update_response : public emitter_message
    {
    public:
        std::shared_ptr<domain::encounter> encounter_ptr;
        
        explicit encounter_update_response(const std::shared_ptr<domain::encounter>& encounter_ptr) : encounter_ptr(encounter_ptr)
        {
        }

        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::encounter_update_response;
        }
    };
}
