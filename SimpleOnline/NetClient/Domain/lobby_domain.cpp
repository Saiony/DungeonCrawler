#include "lobby_domain.h"

#include <algorithm>
using namespace dungeon_client::domain;
using namespace std;

player_lobby_domain::player_lobby_domain(const dungeon_common::model::player_lobby_model model) : name_(model.name), ready_(model.ready)
{
}

std::string player_lobby_domain::get_name()
{
    return name_;
}

std::string player_lobby_domain::get_ready_text() const
{
    return ready_ ? "OK" : "Not OK";
}

bool player_lobby_domain::get_ready()
{
    return ready_;
}

bool player_lobby_domain::get_start_match()
{
    return start_match_;
}

lobby_domain::lobby_domain() = default;

lobby_domain::lobby_domain(dungeon_common::model::lobby_model& model) : start_match(model.start_match)
{
    ranges::for_each(model.players_lobby_status, [&](auto player_lobby_model)
    {
        const player_lobby_domain player_lobby_domain(player_lobby_model);
        players_ready.push_back(player_lobby_domain);
    });
}
