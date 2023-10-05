#pragma once
#include "emitter_message.h"
#include "NetServer/Domain/creature_stat.h"
#include "NetServer/Domain/Player.h"

namespace dungeon_server::domain::message
{
    class bonfire_result_response final : public emitter_message
    {
    public:
        std::shared_ptr<player> story_teller;
        creature_stat upgraded_stat;
        action_log level_up_log;
        std::string story;

        bonfire_result_response(std::shared_ptr<player> story_teller, creature_stat upgraded_stat,
                                action_log level_up_log, std::string story)
            : story_teller(std::move(story_teller)), upgraded_stat(std::move(upgraded_stat)),
              level_up_log(std::move(level_up_log)), story(std::move(story))
        {
        }

        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::bonfire_result_response;
        }
    };
}
