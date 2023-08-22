#pragma once

#include <string>
#include <vector>

#include "player_class.h"
#include "Models/lobby_model.h"

namespace dungeon_client::domain
{
    class player_lobby
    {
    private:
        std::string name_{};
        player_class player_class_{};
        bool ready_{};
        bool start_match_{};

    public:        
        explicit player_lobby(dungeon_common::model::player_lobby_model model);
        std::string get_name();
        player_class get_class();
        std::string get_ready_text() const;
        bool get_ready() const;
        bool get_start_match() const;
    };

    class lobby
    {
    public:
        bool start_match;
        
        explicit lobby(dungeon_common::model::lobby_model& model);
        lobby();
        std::vector<player_lobby> players_ready;
    };
}
