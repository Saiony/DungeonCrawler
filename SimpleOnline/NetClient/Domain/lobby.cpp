#include "lobby.h"

#include <algorithm>
using namespace dungeon_client::domain;
using namespace std;

player_lobby::player_lobby(const dungeon_common::model::player_lobby_model model) : name_(model.name), player_class_(model.player_class.id,
                                                                                    model.player_class.name), ready_(model.ready)
{
}

std::string player_lobby::get_name()
{
    return name_;
}

player_class player_lobby::get_class()
{
    return player_class_;
}

std::string player_lobby::get_ready_text() const
{
    return ready_ ? "OK" : "Not OK";
}

bool player_lobby::get_ready() const
{
    return ready_;
}

bool player_lobby::get_start_match() const
{
    return start_match_;
}

lobby::lobby() = default;

lobby::lobby(dungeon_common::model::lobby_model& model) : start_match(model.start_match)
{
    ranges::for_each(model.players_lobby_status, [&](auto player_lobby_model)
    {
        const player_lobby player_lobby_domain(player_lobby_model);
        players_ready.push_back(player_lobby_domain);
    });
}
