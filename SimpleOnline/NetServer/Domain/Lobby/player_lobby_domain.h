#pragma once
#include <cstdint>
#include <string>

#include "NetServer/Domain/player_classes.h"

namespace dungeon_server::domain::lobby
{
    class player_lobby_domain
    {
    private:
        std::string private_id_;
        char name_[40]{};
        player_class player_class_;
        bool ready_;
    public:
        player_lobby_domain(std::string private_id, const std::string& name, const player_class& player_class, bool ready);
        std::string get_private_id() const;
        bool get_ready() const;
        const char* get_name() const;
        player_class get_player_class();
    
        void set_ready(bool ready);
    };
}

