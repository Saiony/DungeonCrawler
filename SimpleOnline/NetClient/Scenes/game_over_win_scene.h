#pragma once
#include "BaseScene.h"

namespace dungeon_client
{
    class client;
}

namespace dungeon_client::scene
{
    class game_over_win_scene final : base_scene
    {
    public:
        void show() override;
    };
}



