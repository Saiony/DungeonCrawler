#pragma once
#include "creature_stat_types.h"
#include "emitter_message.h"
#include "NetServer/Domain/Player.h"

namespace dungeon_server::domain::message
{
    class bonfire_story_result_response final : public emitter_message
    {
    public:
        std::shared_ptr<player> story_teller;
        dungeon_common::enums::creature_stat_types upgraded_stat{};
        action_log level_up_log;
        std::string story{};

        bonfire_story_result_response(std::shared_ptr<player> story_teller, const dungeon_common::enums::creature_stat_types upgraded_stat,
                                      action_log level_up_log, std::string story)
            : story_teller(std::move(story_teller)), upgraded_stat(upgraded_stat),
              level_up_log(std::move(level_up_log)), story(std::move(story))
        {
        }

        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::bonfire_story_result_response;
        }
    };
}
