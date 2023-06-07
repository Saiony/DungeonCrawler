#pragma once

namespace dungeon_server::game_room
{
    template <typename T>
    class base_state
    {
    public:
        virtual ~base_state() = default;

        virtual void handle_input(const T& game_room, domain::action::base_action action)
        {
        }

        virtual void update(const T& game_room)
        {
        }

        virtual void on_start(const T& game_room)
        {
        }

        virtual void on_end(const T& game_room)
        {
        }
    };
}
