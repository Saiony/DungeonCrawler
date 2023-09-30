#pragma once
#include "base_game_room_state.h"
#include "NetServer/Domain/Message/bonfire_story_teller_response.h"
#include "NetServer/Utility/randomizer.h"

namespace dungeon_server::game_room
{
    class game_room_bonfire_state final : public base_game_room_state
    {
    private:
        std::function<void()> on_state_ended_callback_;
        std::vector<std::shared_ptr<domain::player>> players_;
    public:
        game_room_bonfire_state(std::vector<std::shared_ptr<domain::player>> players,
                                const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_inner_server_msg_callback,
                                std::function<void()> on_state_ended_callback)
            : base_game_room_state(send_inner_server_msg_callback),
              on_state_ended_callback_(std::move(on_state_ended_callback)),
              players_(std::move(players))
        {
        }

        dungeon_common::enums::gameplay_state_type get_gameplay_state_type() override
        {
            return dungeon_common::enums::gameplay_state_type::bonfire;
        }

        void handle_input(const std::shared_ptr<domain::action::base_action>& action_ptr) override
        {
        }

        void on_start() override
        {
        }

        void on_end() override
        {
        }

        void request_story_teller(const std::shared_ptr<domain::player>& client) const
        {
            const int random_index = utility::randomizer::randomize(0, static_cast<int>(std::size(players_) - 1));
            auto story_teller =  players_[random_index];
            
            const auto msg = std::make_shared<domain::message::bonfire_story_teller_response>(client, story_teller);
            send_inner_server_msg_(msg);            
        }
    };
}
