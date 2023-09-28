#pragma once
#include "base_game_room_state.h"

namespace dungeon_server::game_room
{
    class game_room_game_over_lose_state : public base_game_room_state
    {
    public:
        explicit game_room_game_over_lose_state(
            const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_inner_server_msg_callback)
            : base_game_room_state(send_inner_server_msg_callback)
        {
        }

        dungeon_common::enums::gameplay_state_type get_gameplay_state_type() override
        {
            return dungeon_common::enums::gameplay_state_type::game_over_loss;
        }
    };
}
