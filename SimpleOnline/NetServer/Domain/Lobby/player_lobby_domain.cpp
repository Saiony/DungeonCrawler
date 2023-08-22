#include "player_lobby_domain.h"
using namespace dungeon_server::domain::lobby;

player_lobby_domain::player_lobby_domain(std::string private_id, const std::string& name, const player_class& player_class, const bool ready)
                                         : private_id_(std::move(private_id)), player_class_(player_class), ready_(ready)
{
    strcpy_s(name_, name.c_str());
}

std::string player_lobby_domain::get_private_id() const
{
    return private_id_;
}

bool player_lobby_domain::get_ready() const
{
    return ready_;
}

const char* player_lobby_domain::get_name() const
{
    return name_;
}

dungeon_server::domain::player_class player_lobby_domain::get_player_class()
{
    return player_class_;
}

void player_lobby_domain::set_ready(const bool ready)
{
    ready_ = ready;
}
