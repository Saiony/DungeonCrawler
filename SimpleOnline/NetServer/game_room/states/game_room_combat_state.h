#pragma once
#include "base_game_room_state.h"
#include "NetServer/encounter_manager.h"
#include "NetServer/Domain/Encounter.h"
#include "NetServer/Domain/Player.h"
#include "NetServer/Domain/Message/encounter_update_response.h"
#include "NetServer/game_room/combat/base_combat_state.h"

namespace dungeon_server::game_room
{
    class game_room_combat_state final : public base_game_room_state
    {
    private:
        std::shared_ptr<domain::encounter_manager> encounter_manager_;
        combat::base_combat_state state_;
        std::time_t next_turn_time_;
        const int turn_duration_ = 30;

    public:
        explicit game_room_combat_state(std::shared_ptr<domain::encounter_manager> encounter_manager) : encounter_manager_(std::move(encounter_manager))
        {
            next_turn_time_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            next_turn_time_ += turn_duration_;
        }

        void handle_input(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function,
                          const std::shared_ptr<domain::action::base_action>& action) override
        {
            std::string action_log;
            action->use(encounter_manager_->current_encounter, action_log);
            std::cout << action_log << "\n-\n";
            
            encounter_manager_->go_to_next_turn();
            encounter_manager_->current_encounter->active_creature->on_begin_of_turn(encounter_manager_->current_encounter, action_log);  
            
            const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, action_log);
            send_message_function(msg);
            handle_turn(send_message_function);
        }

        void handle_turn(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function)
        {
            domain::base_creature active_creature = *encounter_manager_->current_encounter->active_creature;
            
            if(const auto enemy_ptr = std::dynamic_pointer_cast<domain::base_enemy>(encounter_manager_->current_encounter->active_creature))
            {
                std::cout <<  enemy_ptr->name << "'s turn" << std::endl;
                auto enemy_action_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                enemy_action_time += 5;
                while(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) < enemy_action_time){}

                std::string action_log;
                
                enemy_ptr->on_begin_of_turn(encounter_manager_->current_encounter, action_log);
                enemy_ptr->execute_turn(encounter_manager_->current_encounter, action_log);
                enemy_ptr->on_end_of_turn(encounter_manager_->current_encounter, action_log);
                
                encounter_manager_->go_to_next_turn();
                encounter_manager_->current_encounter->active_creature->on_begin_of_turn(encounter_manager_->current_encounter, action_log);  
                
                const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, action_log);
                send_message_function(msg);
                handle_turn(send_message_function);
                start_timeout_timer();

                std::cout << action_log;
            }
            else if(const auto player_ptr = std::dynamic_pointer_cast<domain::player>(encounter_manager_->current_encounter->active_creature))
            {
                std::cout <<  player_ptr->name << "'s turn" << std::endl;
                std::string action_log;
              
                if(!player_ptr->can_execute_turn())
                {
                    player_ptr->on_end_of_turn(encounter_manager_->current_encounter, action_log);
                    encounter_manager_->go_to_next_turn();
                    encounter_manager_->current_encounter->active_creature->on_begin_of_turn(encounter_manager_->current_encounter, action_log);  
                    const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, action_log);
                    send_message_function(msg);
                    handle_turn(send_message_function);
                }
                                
                start_timeout_timer();
            }
        }

        void update(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function) override
        {
            const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            if(now <=  next_turn_time_)
                return;
            
            encounter_manager_->current_encounter->go_to_next_turn();          
            const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, "timeout");
            send_message_function(msg);
            
            handle_turn(send_message_function);
        }

        void on_start() override
        {
        }

        void on_end() override
        {
        }

        void start_timeout_timer()
        {
            next_turn_time_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            next_turn_time_ += turn_duration_;
        }
    };
}
