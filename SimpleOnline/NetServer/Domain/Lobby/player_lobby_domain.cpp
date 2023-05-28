#include "player_lobby_domain.h"
using namespace  dungeon_server::domain::lobby;

player_lobby_domain::player_lobby_domain(const std::string& private_id, const std::string& name, const bool ready) : private_id_(private_id), ready_(ready)
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

void player_lobby_domain::set_ready(const bool ready)
{
    ready_ = ready;
}
