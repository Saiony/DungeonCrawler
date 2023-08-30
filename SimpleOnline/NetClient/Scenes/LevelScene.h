#pragma once
#include <memory>
#include "BaseScene.h"
#include "../client.h"

namespace dungeon_client::scene
{
    class level_scene : public base_scene
    {
    private:
        std::shared_ptr<client> client_ptr_ = nullptr;
        
        void on_game_over(bool players_won) const;
        void read_action_target(domain::encounter& encounter, std::shared_ptr<domain::action> player_action_ptr) const;
    public:        
        explicit level_scene(const std::shared_ptr<client>& client_ptr);
        void show() override;
        void print_combat(const dungeon_client::domain::encounter& encounter) const;
        void handle_player_input(domain::encounter& encounter) const;
    };
}
