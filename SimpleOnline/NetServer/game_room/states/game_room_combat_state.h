#pragma once
#include "base_game_room_state.h"
#include "NetServer/encounter_manager.h"
#include "NetServer/Domain/Encounter.h"
#include "NetServer/Domain/Player.h"
#include "NetServer/Domain/Message/encounter_update_response.h"

namespace dungeon_server::game_room
{
    class game_room_combat_state final : public base_game_room_state
    {
    private:
        const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_inner_server_msg_;
        std::shared_ptr<domain::encounter_manager> encounter_manager_;
        std::time_t next_turn_time_;
        const int turn_duration_ = 30;
        bool encounter_finished_ = false;

    public:
        explicit game_room_combat_state(std::shared_ptr<domain::encounter_manager> encounter_manager,
                                        const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_inner_server_msg)
            : send_inner_server_msg_(send_inner_server_msg), encounter_manager_(std::move(encounter_manager))
        {
            next_turn_time_ = std::numeric_limits<time_t>::max();
        }

        void handle_input(const std::shared_ptr<domain::action::base_action>& action) override
        {
            domain::action_log action_log;
            action->use(encounter_manager_->current_encounter, action_log);

            const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, action_log);
            send_inner_server_msg_(msg);

            encounter_manager_->go_to_next_turn(action_log);

            handle_turn();
        }

        void handle_turn()
        {
            std::cout << "\nHandle Turn";
            if (encounter_finished_)
                return;

            const auto active_creature = encounter_manager_->current_encounter->active_creature;

            if (const auto enemy_ptr = std::dynamic_pointer_cast<domain::base_enemy>(active_creature))
            {
                std::cout << enemy_ptr->name << "'s turn" << std::endl;
                auto enemy_action_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                enemy_action_time += 5;
                while (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) < enemy_action_time)
                {
                }

                domain::action_log action_log;

                enemy_ptr->on_begin_of_turn(encounter_manager_->current_encounter, action_log);
                enemy_ptr->execute_turn(encounter_manager_->current_encounter, action_log);
                enemy_ptr->on_end_of_turn(encounter_manager_->current_encounter, action_log);

                encounter_manager_->go_to_next_turn(action_log);

                const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, action_log);
                start_timeout_timer();
                send_inner_server_msg_(msg);

                handle_turn();
            }
            else if (const auto player_ptr = std::dynamic_pointer_cast<domain::player>(active_creature))
            {
                std::cout << player_ptr->name << "'s turn" << std::endl;
                domain::action_log action_log;
                active_creature->on_begin_of_turn(encounter_manager_->current_encounter, action_log);

                if (!player_ptr->can_execute_turn())
                {
                    player_ptr->on_end_of_turn(encounter_manager_->current_encounter, action_log);
                    encounter_manager_->go_to_next_turn(action_log);
                    const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, action_log);
                    send_inner_server_msg_(msg);

                    handle_turn();
                    return;
                }

                const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, action_log);
                send_inner_server_msg_(msg);
                start_timeout_timer();
            }
        }

        void update(const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_message_function) override
        {
            const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            if (now <= next_turn_time_)
                return;

            encounter_manager_->current_encounter->go_to_next_turn();
            domain::action_log log;
            log.add_log("timeout");
            const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, log);
            send_message_function(msg);

            handle_turn();
        }

        void on_start() override
        {
            encounter_manager_->start_encounter();

            //TODO: this needs to be a match_start_response and the client needs to handle that
            domain::action_log log;
            const auto msg = std::make_shared<domain::message::encounter_update_response>(encounter_manager_->current_encounter, log);
            send_inner_server_msg_(msg);

            start_timeout_timer();
        }

        void on_end() override
        {
            std::cout << "\nCombat State - On End";
            encounter_finished_ = true;
            encounter_manager_->end_encounter();
        }

        void start_timeout_timer()
        {
            next_turn_time_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) + turn_duration_;
            std::cout << "\nTimer set";
        }
    };
}
