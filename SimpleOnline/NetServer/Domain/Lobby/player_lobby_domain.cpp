#include "player_lobby_domain.h"
using namespace  dungeon_server::domain::lobby;

player_lobby_domain::player_lobby_domain(const uint16_t private_id, const std::string& name, const bool ready) : ready_(ready), private_id_(private_id)
{
    strcpy_s(name_, name.c_str());
}

uint16_t player_lobby_domain::get_id() const
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
