#pragma once
#include "base_game_room_state.h"
#include "NetClient/client.h"
#include "NetServer/Domain/Message/story_read_response.h"
#include "NetServer/Domain/Message/story_response.h"

namespace dungeon_server::game_room
{
    class game_room_story_state final : public base_game_room_state
    {
    private:
        uint8_t level_;
        std::map<std::string, bool> players_confirmed_;
        std::function<void()> on_state_ended_callback_;
    public:
        explicit game_room_story_state(const uint8_t level, std::vector<std::shared_ptr<domain::player>> players,
                                       const std::function<void(std::shared_ptr<domain::message::emitter_message>)>& send_inner_server_msg_callback,
                                       std::function<void()> on_state_ended_callback)
            : base_game_room_state(send_inner_server_msg_callback),
              level_(level), on_state_ended_callback_(std::move(on_state_ended_callback))
        {
            std::ranges::for_each(players, [this](auto player)
            {
                players_confirmed_[player->private_id] = false;
            });
        }

        dungeon_common::enums::gameplay_state_type get_gameplay_state_type() override
        {
            return dungeon_common::enums::gameplay_state_type::story;
        }

        domain::story_log generate_story() const
        {
            domain::story_log story;

            switch (level_)
            {
            case 1:
                {
                    story.add_log("CHAPTER 1 - The Beginning");
                    story.add_log("It's a peaceful night, no stars in the sky and no wind to shake the trees of the forest");
                    story.add_log("In front of you, a shadow grows taller...");
                    story.add_log("You know what it is, this was your goal for months");
                    story.add_log("The Dragon Mountain");
                    story.add_log("Lair of the Necromancer");
                    story.add_log("...");
                    story.add_log("But you are tired from your long journey, and the mountain can wait a little longer");
                    story.add_log("A tent is raised and a fire is lit");
                    story.add_log("You sleep quiet with your belly full of grilled fish");
                    story.add_log("...");
                    story.add_log("You wake up in the middle of the night");
                    story.add_log("Something's wrong...");
                    story.add_log("You see a shadow with narrow yellow eyes lurking behind the trees");
                    story.add_log("A hungry wolf attacks you!!");
                    break;
                }
            case 2:
                {
                    story.add_log("CHAPTER 2 - Into the dungeon");
                    story.add_log("HELLO WORLD 2");
                    break;
                }
            case 3:
                {
                    story.add_log("HELLO WORLD 3");
                    break;
                }
            default:
                {
                    break;
                }
            }

            return story;
        }

        void update() override
        {
        }

        void on_start() override
        {
        }

        void on_end() override
        {
        }

        void request_story(const std::shared_ptr<domain::player>& player) const
        {
            const auto msg = std::make_shared<domain::message::story_response>(generate_story(), player);
            send_inner_server_msg_(msg);
        }

        void confirm_story_read(const std::shared_ptr<domain::player>& player)
        {
            if (!players_confirmed_.contains(player->private_id))
                throw std::exception("invalid player id");

            players_confirmed_[player->private_id] = true;

            const int confirmed_count = std::ranges::count_if(players_confirmed_, [this](auto player_confirmed)
            {
                return player_confirmed.second == true;
            });

            if (confirmed_count == players_confirmed_.size())
            {
                const auto msg = std::make_shared<domain::message::story_read_response>(true);
                send_inner_server_msg_(msg);
                on_state_ended_callback_();
            }
        }
    };
}
