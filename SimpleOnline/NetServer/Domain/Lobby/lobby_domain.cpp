#include "lobby_domain.h"

#include <algorithm>

bool dungeon_server::domain::lobby::lobby_domain::can_start_match()
{
    const auto start = std::ranges::all_of(players_ready, [](const player_lobby_domain player)
    {
        return !player.get_private_id().empty() && player.get_ready();
    });

    return start;
}
