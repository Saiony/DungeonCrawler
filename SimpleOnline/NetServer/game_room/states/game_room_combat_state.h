#pragma once
#include "base_game_room_state.h"
#include "NetServer/Domain/Encounter.h"
#include "NetServer/Domain/Player.h"
#include "NetServer/Domain/Message/encounter_update_response.h"
#include "NetServer/game_room/combat/base_combat_state.h"

namespace dungeon_server::game_room
{
    class game_room_combat_state final : public base_game_room_state
    {
    private:
        std::shared_ptr<domain::encounter> encounter_ptr_;
        domain::player active_player_;
        combat::base_combat_state state_;

    public:
        explicit game_room_combat_state(const std::shared_ptr<domain::encounter>& encounter_ptr) : encounter_ptr_(encounter_ptr),
                                                                                                   active_player_(encounter_ptr->players[0])
        {
        }

        void handle_input(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function,
                          const std::shared_ptr<domain::action::base_action>& action) override
        {
            action->use(encounter_ptr_);
            const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_ptr_);
            send_message_function(msg);
        }

        void update() override
        {
        }

        void on_start() override
        {
            //falar pro player que eh o turno dele
        }

        void on_end() override
        {
        }
    };
}
