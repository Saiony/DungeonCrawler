#include "lobby_domain.h"

#include <algorithm>

bool dungeon_server::domain::lobby::lobby_domain::start_match()
{
    const auto start = std::ranges::all_of(players_ready, [](const player_lobby_domain player)
    {
        return player.get_id() != 0 && player.get_ready();
    });

    return start;
}
