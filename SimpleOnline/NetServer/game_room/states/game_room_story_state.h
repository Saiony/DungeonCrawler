#pragma once
#include "base_game_room_state.h"

namespace dungeon_server::game_room
{
    class game_room_story_state final : base_game_room_state
    {
    public:
        void handle_input(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function,
                          const std::shared_ptr<domain::action::base_action>& action_ptr) override
        {
        
        }

        void update(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function) override
        {
        
        }

        void on_start() override
        {
        
        }

        void on_end() override
        {
        
        }
    };
}
