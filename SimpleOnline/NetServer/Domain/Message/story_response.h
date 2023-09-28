#pragma once
#include "emitter_message.h"
#include "NetServer/Domain/story_log.h"

namespace dungeon_server::domain::message
{
    class story_response final : public emitter_message
    {
    public:
        story_log story;
        std::shared_ptr<player> player;

        explicit story_response(story_log story, std::shared_ptr<domain::player> player)
            : story(std::move(story)), player(std::move(player))
        {
        }

        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::story_response;
        }
    };
}
