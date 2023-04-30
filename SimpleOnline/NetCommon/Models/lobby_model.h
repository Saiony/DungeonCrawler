#pragma once
#include <array>
#include <string>
#include <tuple>
#include <vector>

namespace dungeon_common::model
{
    struct player_lobby_model
    {
        char name[40]{};
        bool ready;
        
        player_lobby_model(const char* player_name, bool ready);
        player_lobby_model();
        void set_ready(bool ready_state);
    };

    struct lobby_model
    {
        std::array<player_lobby_model, 3> players_lobby_status;
        bool start_match;
        
        lobby_model();
    };
}
