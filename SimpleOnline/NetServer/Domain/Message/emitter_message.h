#pragma once
#include "net_message.h"

namespace dungeon_server::domain::message
{
    class emitter_message
    {
    public:
        virtual ~emitter_message() = default;

        virtual dungeon_common::custom_msg_types get_id()
        {
            return dungeon_common::custom_msg_types::unknown;
        }
    };
}