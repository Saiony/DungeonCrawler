#pragma once
#include <cstdint>
#include <string>

namespace dungeon_server::domain::lobby
{
    class player_lobby_domain
    {
    private:
        char name_[40]{};
        std::string private_id_;
        bool ready_;
    public:
        player_lobby_domain(const std::string& private_id, const std::string& name, bool ready);
        std::string get_private_id() const;
        bool get_ready() const;
        const char* get_name() const;
    
        void set_ready(bool ready);
    };
}

