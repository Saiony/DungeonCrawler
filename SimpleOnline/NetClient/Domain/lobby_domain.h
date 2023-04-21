#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "Models/lobby_model.h"

namespace dungeon_client::domain
{
    class player_lobby_domain
    {
    private:
        std::string name_{};
        bool ready_{};
    public:
        explicit player_lobby_domain(dungeon_common::model::player_lobby_model model);
        std::string get_name();
        std::string get_ready() const;
    };

    class lobby_domain
    {
    public:
        std::vector<player_lobby_domain> players_ready_;    
        explicit lobby_domain(dungeon_common::model::lobby_model& model);
    };
}
