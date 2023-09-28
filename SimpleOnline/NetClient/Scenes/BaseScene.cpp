#include "BaseScene.h"

void dungeon_client::scene::base_scene::show()
{
}

void dungeon_client::scene::base_scene::subscribe_on_end(const std::function<void()>& callback)
{
    on_scene_ended_callback_ = callback;
}
