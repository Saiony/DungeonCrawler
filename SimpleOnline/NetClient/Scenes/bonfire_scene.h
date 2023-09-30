#pragma once
#include "BaseScene.h"
#include "../client.h"

namespace dungeon_client::scene
{
    class bonfire_scene final : public base_scene
    {
    private:
        std::shared_ptr<client> client_ptr_ = nullptr;
    public:
        explicit bonfire_scene(std::shared_ptr<client> client_ptr);
        void show() override;
    };
}
