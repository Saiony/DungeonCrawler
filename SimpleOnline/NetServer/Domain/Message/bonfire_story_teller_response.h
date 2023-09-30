#pragma once

#include "emitter_message.h"

namespace dungeon_server::domain::message
{
    class bonfire_story_teller_response final : public emitter_message
    {
    public:
        std::shared_ptr<player> client;
        std::shared_ptr<player> story_teller;

        explicit bonfire_story_teller_response(std::shared_ptr<player> client, std::shared_ptr<player> story_teller)
            : client(std::move(client)), story_teller(std::move(story_teller))
        {
        }

        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::bonfire_story_teller_response;
        }
    };
}
