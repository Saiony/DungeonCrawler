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
        
    public:        
        explicit level_scene(const std::shared_ptr<client>& client_ptr);
        void show() override;
        void print_combat(const dungeon_client::domain::encounter& encounter) const;
    };
}
