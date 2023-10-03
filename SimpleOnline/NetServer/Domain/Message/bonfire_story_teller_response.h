#pragma once

#include "emitter_message.h"
#include "NetServer/Domain/creature_stat.h"

namespace dungeon_server::domain::message
{
    class bonfire_story_teller_response final : public emitter_message
    {
    public:
        std::shared_ptr<player> client;
        std::shared_ptr<player> story_teller;
        uint16_t max_characters;
        std::vector<creature_stat> stats;

        explicit bonfire_story_teller_response(std::shared_ptr<player> client, std::shared_ptr<player> story_teller, const uint16_t max_characters,
                                               std::vector<creature_stat> stats)
            : client(std::move(client)), story_teller(std::move(story_teller)),
              max_characters(max_characters), stats(std::move(stats))
        {
        }

        dungeon_common::custom_msg_types get_id() override
        {
            return dungeon_common::custom_msg_types::bonfire_story_teller_response;
        }
    };
}
