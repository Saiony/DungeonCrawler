#pragma once
#include "base_game_room_state.h"
#include "NetServer/Domain/Message/bonfire_result_response.h"
#include "NetServer/Domain/Message/bonfire_story_teller_response.h"
#include "NetServer/Utility/randomizer.h"

namespace dungeon_server::game_room
{
    class game_room_bonfire_state final : public base_game_room_state
    {
    private:
        std::function<void()> on_state_ended_callback_;
        std::vector<std::shared_ptr<domain::player>> players_;
        std::shared_ptr<domain::player> story_teller_;
        const uint16_t max_characters_ = 250;

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
            const int random_index = utility::randomizer::randomize(0, static_cast<int>(std::size(players_) - 1));
            story_teller_ = players_[random_index];
        }

        void on_end() override
        {
        }

        //TODO: criar var e inicializar no start.
        //Ao requisitar, somente retornamos
        //Dessa forma, podemos criar um metodo get_upgradable_stats(creature_stat_types)
        std::vector<creature_stat> get_upgradable_stats() const 
        {
            std::vector<creature_stat> stats
            {
                {dungeon_common::enums::creature_stat_types::attack_damage, "attack damage"},
                {dungeon_common::enums::creature_stat_types::ability_power, "ability power"},
                {dungeon_common::enums::creature_stat_types::max_health, "health"}
            };

            return stats;
        }


        void increment_players_stat(dungeon_common::enums::creature_stat_types stat_id, domain::action_log& log)
        {
            std::ranges::for_each(players_, [&stat_id, &log](auto player)
            {
                player->level_up(stat_id, log);
            });
        }

        void request_story_teller(const std::shared_ptr<domain::player>& client) const
        {
            const auto msg = std::make_shared<domain::message::bonfire_story_teller_response>(client, story_teller_,
                                                                                              max_characters_, get_upgradable_stats());
            send_inner_server_msg_(msg);
        }

        void receive_story(const std::shared_ptr<domain::player>& client,
                           dungeon_common::enums::creature_stat_types stat_id,
                           const std::string& story)
        {
            if (client->private_id != story_teller_->private_id)
                throw std::exception("Invalid story teller");

            domain::action_log log;
            increment_players_stat(stat_id, log);

            auto xa = get_upgradable_stats();
            auto creature_stat = *std::ranges::find_if(xa, [&stat_id](auto stat)
            {
                return stat.id == stat_id;
            });

            const auto msg = std::make_shared<domain::message::bonfire_result_response>(client, creature_stat, log, story);
            send_inner_server_msg_(msg);
            on_state_ended_callback_();
        }
    };
}
