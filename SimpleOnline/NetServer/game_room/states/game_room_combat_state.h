﻿#pragma once
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
        combat::base_combat_state state_;
        std::time_t next_turn_time_;
        const int turn_duration_ = 10;

    public:
        explicit game_room_combat_state(std::shared_ptr<domain::encounter> encounter_ptr) : encounter_ptr_(std::move(encounter_ptr))
        {
            next_turn_time_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            next_turn_time_ += turn_duration_;
        }

        void handle_input(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function,
                          const std::shared_ptr<domain::action::base_action>& action) override
        {
            std::string action_log = action->use(encounter_ptr_);
            remove_dead_creatures();
            std::cout << action_log << "\n-\n"; 
            encounter_ptr_->go_to_next_turn();
            
            const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_ptr_, action_log);
            send_message_function(msg);
            handle_turn(send_message_function);
        }

        void handle_turn(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function)
        {
            domain::base_creature active_creature = *encounter_ptr_->active_creature;
            
            if(const auto enemy_ptr = std::dynamic_pointer_cast<domain::base_enemy>(encounter_ptr_->active_creature))
            {
                std::cout <<  enemy_ptr->name << "'s turn" << std::endl;
                auto enemy_action_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                enemy_action_time += 5;
                while(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) < enemy_action_time){}
                
                auto action_log = enemy_ptr->execute_turn(encounter_ptr_);
                remove_dead_creatures();
                encounter_ptr_->go_to_next_turn();
                
                const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_ptr_, action_log);
                send_message_function(msg);
                handle_turn(send_message_function);
                start_timeout_timer();
            }
            else if(const auto player_ptr = std::dynamic_pointer_cast<domain::player>(encounter_ptr_->active_creature))
            {
                std::cout <<  player_ptr->name << "'s turn" << std::endl;
                start_timeout_timer();
            }
        }

        void update(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function) override
        {
            const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            if(now <=  next_turn_time_)
                return;
            
            encounter_ptr_->go_to_next_turn();
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

        void remove_dead_creatures() const
        {
            std::erase_if(encounter_ptr_->creatures, [](auto creature)
            {
                return creature->alive == false;
            });

            std::erase_if(encounter_ptr_->players, [](auto player)
            {
                return player->alive == false;
            });
            
            std::erase_if(encounter_ptr_->enemies, [](auto enemy)
            {
                return enemy->alive == false;
            });
        }
    };
}
