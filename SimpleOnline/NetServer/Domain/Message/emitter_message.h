#pragma once
#include "net_message.h"

class emitter_message
{
public:
    virtual dungeon_common::custom_msg_types get_id()
    {
        return dungeon_common::custom_msg_types::unknown;
    }
};