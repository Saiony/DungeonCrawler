#pragma once
#include <memory>

#include "BaseScene.h"
#include "../client.h"

namespace dungeon_client::scene
{
    class lobby_scene : public base_scene
    {
    private:
        bool ready_ = false;
        std::shared_ptr<client> client_ptr_ = nullptr;
        
        void wait_player_ready(const std::shared_ptr<client>& client_ptr, bool ready);
        void start_match(const domain::lobby& lobby) const;
        void print_lobby(domain::lobby lobby) const;
    public:        
        explicit lobby_scene(const std::shared_ptr<client>& client_ptr);
        void show() override;
    };
}
