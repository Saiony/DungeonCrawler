#pragma once
#include <memory>

#include "BaseScene.h"
#include "../client.h"

namespace dungeon_client::scene
{
    class gameplay_scene final : public base_scene
    {
    private:
        std::shared_ptr<client> client_ptr_ = nullptr;
    public:
        explicit gameplay_scene(std::shared_ptr<client> client_ptr);
        void show() override;
        void on_state_ended();
        void request_new_state();
    };
}
