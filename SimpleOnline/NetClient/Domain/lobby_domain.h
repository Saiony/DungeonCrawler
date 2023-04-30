#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "../../NetServer/Domain/Lobby/player_lobby_domain.h"
#include "Models/lobby_model.h"

namespace dungeon_client::domain
{
    class player_lobby_domain
    {
    private:
        std::string name_{};
        bool ready_{};
        bool start_match_;

    public:        
        explicit player_lobby_domain(dungeon_common::model::player_lobby_model model);
        std::string get_name();
        std::string get_ready_text() const;
        bool get_ready();
        bool get_start_match();
    };

    class lobby_domain
    {
    public:
        bool start_match;
        
        explicit lobby_domain(dungeon_common::model::lobby_model& model);
        lobby_domain();
        std::vector<player_lobby_domain> players_ready;
    };
}
