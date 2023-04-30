#pragma once
#include <vector>
#include "player_lobby_domain.h"


namespace dungeon_server::domain::lobby
{
    class lobby_domain
    {
    public:
        std::vector<player_lobby_domain> players_ready;
        
        bool start_match();
    };
}
