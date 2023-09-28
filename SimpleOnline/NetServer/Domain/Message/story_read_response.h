#pragma once

#include "emitter_message.h"

namespace dungeon_server::domain::message
{
    class story_read_response final : public emitter_message
    {
    public:
        bool everyone_read;

        explicit story_read_response(const bool everyone_read)
            : everyone_read(everyone_read)
        {
        }

        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::story_read_response;
        }
    };
}
