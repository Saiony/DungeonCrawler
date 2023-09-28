#pragma once
#include <memory>

#include "NetServer/Domain/encounter_manager.h"
#include "NetServer/Domain/Actions/base_action.h"
#include "NetServer/Domain/Message/emitter_message.h"
#include "states/base_game_room_state.h"

namespace dungeon_server::game_room
{
    class game_room
    {
    private:
        std::vector<std::shared_ptr<domain::player>> players_;
        std::shared_ptr<domain::encounter_manager> encounter_manager_;
        bool game_over_ = false;
        uint8_t level_ = 1;
        uint8_t max_level_ = 3;

        void on_state_ended();
        void on_players_lost();
    public:
        std::shared_ptr<base_game_room_state> state_ptr;
        
        game_room(std::vector<std::shared_ptr<domain::player>> players, const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function);
        void request_story(const std::shared_ptr<domain::player>& player) const;
        void go_to_next_state();
        std::function<void(std::shared_ptr<domain::message::emitter_message>)> send_inner_message;
        void player_match_start_request(std::shared_ptr<domain::player>& player) const;
        void set_state(const std::shared_ptr<base_game_room_state>& state);
        void handle_player_input(const std::shared_ptr<domain::action::base_action>& action_ptr) const;
        void set_story_read(const std::shared_ptr<domain::player>& player) const;
        void update() const;
    };
}
