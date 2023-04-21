#include "lobby_domain.h"

#include <algorithm>
using namespace dungeon_client::domain;
using namespace std;

player_lobby_domain::player_lobby_domain(const dungeon_common::model::player_lobby_model model) : name_(model.name_), ready_(model.ready_)
{
}
std::string player_lobby_domain::get_name()
{
    return name_;
}

std::string player_lobby_domain::get_ready() const
{
    return ready_ ? "OK" : "Not OK";
}

lobby_domain::lobby_domain(dungeon_common::model::lobby_model& model)
{
    ranges::for_each(model.players_lobby_status, [&](auto player_lobby_model)
    {
        const player_lobby_domain player_lobby_domain(player_lobby_model);
        players_ready_.push_back(player_lobby_domain);
    });
}
