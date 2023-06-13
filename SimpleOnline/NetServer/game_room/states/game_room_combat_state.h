#pragma once
#include "base_game_room_state.h"
#include "NetClient/Domain/base_creature.h"
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
        combat::base_combat_state state_;
        std::time_t next_turn_time_;
        const int turn_duration_ = 5;

    public:
        explicit game_room_combat_state(const std::shared_ptr<domain::encounter>& encounter_ptr) : encounter_ptr_(encounter_ptr)
        {
            next_turn_time_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            next_turn_time_ += turn_duration_;
        }

        void handle_input(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function,
                          const std::shared_ptr<domain::action::base_action>& action) override
        {
            action->use(encounter_ptr_);
            const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_ptr_);
            send_message_function(msg);
        }

        void update(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function) override
        {
            const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            if(now <=  next_turn_time_)
                return;
            
            encounter_ptr_->go_to_next_turn();
            
            domain::base_creature active_creature = *encounter_ptr_->active_creature;
            
            if(const auto enemy_ptr = std::dynamic_pointer_cast<domain::base_enemy>(encounter_ptr_->active_creature))
            {
                enemy_ptr->execute_turn();
                encounter_ptr_->go_to_next_turn();
            }
            if(const auto player_ptr = std::dynamic_pointer_cast<domain::player>(encounter_ptr_->active_creature))
            {
                std::cout <<  player_ptr->name << " turn" << std::endl;
                const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_ptr_);
                send_message_function(msg);
            }
            
            next_turn_time_ += turn_duration_;
        }

        void on_start() override
        {
        }

        void on_end() override
        {
        }
    };
}
