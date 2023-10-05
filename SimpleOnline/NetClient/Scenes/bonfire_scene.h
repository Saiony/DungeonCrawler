#pragma once
#include "BaseScene.h"
#include "../client.h"

namespace dungeon_client::scene
{
    class bonfire_scene final : public base_scene
    {
    private:
        std::shared_ptr<client> client_ptr_ = nullptr;
        domain::creature_stats chosen_stat_;

        void print_header() const;
        void handle_wrong_player_input();
        void handle_stat_input(domain::bonfire_story_telling story_telling);
        void print_story_request(const domain::bonfire_story_telling& story_telling);
        void handle_story_input(const domain::bonfire_story_telling& story_telling);
    public:
        void print_bonfire_result(const domain::bonfire_result& bonfire_result) const;
        explicit bonfire_scene(std::shared_ptr<client> client_ptr);
        void show() override;
    };
}
