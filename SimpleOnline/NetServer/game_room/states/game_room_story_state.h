#pragma once
#include "base_game_room_state.h"
#include "NetServer/Domain/Message/story_response.h"

namespace dungeon_server::game_room
{
    class game_room_story_state final : base_game_room_state
    {
    private:
        uint8_t level_;
    public:
        explicit game_room_story_state(const uint8_t level,
                                       const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_inner_server_msg_callback)
            : base_game_room_state(send_inner_server_msg_callback), level_(level)
        {
        }

        void update() override
        {
        }

        void on_start() override
        {
            domain::story_log story;
            story.add_log("HELLO WORLD");

            const auto msg = std::make_shared<domain::message::story_response>(story);
            send_inner_server_msg_(msg);
        }

        void on_end() override
        {
        }
    };
}
