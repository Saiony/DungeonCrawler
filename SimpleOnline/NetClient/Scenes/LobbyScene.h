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
        
        void wait_player_ready(const shared_ptr<client>& client_ptr, bool ready);
        void print_lobby(domain::lobby_domain lobby) const;
    public:        
        explicit lobby_scene(const shared_ptr<client>& client_ptr);
        void show() override;
    };
}
