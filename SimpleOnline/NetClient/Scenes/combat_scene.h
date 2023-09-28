#pragma once
#include <memory>
#include "BaseScene.h"
#include "../client.h"

namespace dungeon_client::scene
{
    class combat_scene final : public base_scene
    {
    private:
        std::shared_ptr<client> client_ptr_ = nullptr;
        
        void on_combat_ended() const;
        void read_action_target(domain::encounter& encounter, std::shared_ptr<domain::action> player_action_ptr) const;
    public:        
        explicit combat_scene(const std::shared_ptr<client>& client_ptr);
        void show() override;
        void print_combat(const domain::encounter& encounter) const;
        void handle_player_input(domain::encounter& encounter) const;
    };
}
