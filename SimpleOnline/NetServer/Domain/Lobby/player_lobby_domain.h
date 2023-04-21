#pragma once
#include <cstdint>
#include <string>

namespace dungeon_server::domain::lobby
{
    class player_lobby_domain
    {
    private:
        char name_[40]{};
        bool ready_;
        uint16_t private_id_;
    public:
        player_lobby_domain(uint16_t private_id, const std::string& name, bool ready);
        uint16_t get_id() const;
        bool get_ready() const;
        const char* get_name() const;
    
        void set_ready(bool ready);
    };
}

