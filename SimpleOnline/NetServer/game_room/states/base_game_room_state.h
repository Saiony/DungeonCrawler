#pragma once
#include <memory>

#include "gameplay_state_type.h"
#include "NetServer/Domain/Actions/base_action.h"

namespace dungeon_server::game_room
{
    class base_game_room_state
    {
    protected:
        const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_inner_server_msg_;
    public:
        virtual ~base_game_room_state() = default;

        explicit base_game_room_state(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_inner_server_msg_callback)
            : send_inner_server_msg_(send_inner_server_msg_callback)
        {
        }

        virtual void handle_input(const std::shared_ptr<domain::action::base_action>& action_ptr)
        {
        }

        virtual void update()
        {
        }

        virtual void on_start()
        {
        }

        virtual void on_end()
        {
        }

        virtual dungeon_common::enums::gameplay_state_type get_gameplay_state_type() = 0;
    };
}
