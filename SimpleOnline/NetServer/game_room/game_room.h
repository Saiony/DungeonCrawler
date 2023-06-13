#pragma once
#include <memory>
#include "NetServer/Domain/Actions/base_action.h"
#include "NetServer/Domain/Message/emitter_message.h"
#include "states/base_game_room_state.h"

namespace dungeon_server::game_room
{
    class game_room
    {
    private:
        std::vector<std::shared_ptr<domain::player>> players_;
        std::shared_ptr<domain::encounter> encounter_;
        std::unique_ptr<base_game_room_state> state_ptr_;

        std::shared_ptr<domain::encounter> generate_encounter() const;
    public:
        game_room(std::vector<std::shared_ptr<domain::player>> players, const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function);
        std::function<void(std::shared_ptr<domain::message::emitter_message>)> send_inner_message;
        void player_match_start_request(std::shared_ptr<domain::player>& player);
        void set_state(const base_game_room_state& state);
        void handle_player_input(const std::shared_ptr<domain::action::base_action>& action_ptr) const;
        void update() const;
    };
}
