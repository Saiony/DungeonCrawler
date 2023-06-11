#pragma once
#include <memory>
#include "NetServer/Domain/Actions/base_action.h"

namespace dungeon_server::game_room
{
    class base_game_room_state
    {
    public:
        virtual void handle_input(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function,
                                  const std::shared_ptr<domain::action::base_action>& action_ptr)
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
    };
}