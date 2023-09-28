#pragma once
#include <functional>

namespace dungeon_client::scene
{
    class base_scene
    {
    protected:
        std::function<void()> on_scene_ended_callback_;
    public:
        virtual ~base_scene() = default;
        virtual void show();

        void subscribe_on_end(const std::function<void()>& callback);
    };
}
