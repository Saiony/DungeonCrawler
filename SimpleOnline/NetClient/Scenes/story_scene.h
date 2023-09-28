#pragma once
#include <memory>
#include "BaseScene.h"
#include "../client.h"

namespace dungeon_client::scene
{
    class story_scene : public base_scene
    {
    private:
        std::shared_ptr<client> client_ptr_ = nullptr;
        
        void print_story(domain::story story) const;
    public:
        explicit story_scene(std::shared_ptr<client> client_ptr);
        void show() override;
    };
}
