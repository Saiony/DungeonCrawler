#pragma once
#include "base_game_room_state.h"
#include "NetServer/Domain/Message/story_response.h"

namespace dungeon_server::game_room
{
    class game_room_story_state final : public base_game_room_state
    {
    private:
        uint8_t level_;
    public:
        explicit game_room_story_state(const uint8_t level,
                                       const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_inner_server_msg_callback)
            : base_game_room_state(send_inner_server_msg_callback), level_(level)
        {
        }

        dungeon_common::enums::gameplay_state_type get_gameplay_state_type() override
        {
            return dungeon_common::enums::gameplay_state_type::story;
        }

        domain::story_log generate_story() const
        {
            domain::story_log story;

            switch (level_)
            {
            case 1:
                {
                    story.add_log("HELLO WORLD 1");
                    break;
                }
            case 2:
                {
                    story.add_log("HELLO WORLD 2");
                    break;
                }
            case 3:
                {
                    story.add_log("HELLO WORLD 3");
                    break;
                }
            default:
                {
                    break;
                }
            }

            return story;
        }

        void update() override
        {
        }

        void on_start() override
        {
            const auto msg = std::make_shared<domain::message::story_response>(generate_story());
            send_inner_server_msg_(msg);
        }

        void on_end() override
        {
        }
    };
}
