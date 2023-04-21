#pragma once
#include <array>
#include <string>
#include <tuple>
#include <vector>

namespace dungeon_common::model
{
    struct player_lobby_model
    {
        char name_[40]{};
        bool ready_{};
        
        player_lobby_model(const char* name, bool ready);
        player_lobby_model();
        void set_ready(bool ready);
    };

    struct lobby_model
    {
        std::array<player_lobby_model, 3> players_lobby_status;
        lobby_model();
    };
}
