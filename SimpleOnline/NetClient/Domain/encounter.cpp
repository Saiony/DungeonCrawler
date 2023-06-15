#include "encounter.h"

#include "../Scenes/CharacterCreationScene.h"

dungeon_client::domain::encounter::encounter(std::vector<enemy> enemies, std::vector<player> players, std::string active_player_id)
                                            : enemies(std::move(enemies)), players(std::move(players))
{
    const auto active_player_it = std::ranges::find_if(this->players, [&active_player_id](auto player)
    {
        return player.id == active_player_id;
    });

    if(active_player_it == std::end(this->players))
        throw std::logic_error("Couldn't find player id - " + active_player_id);

    active_creature_ptr = std::make_unique<base_creature>(*active_player_it);
}

bool dungeon_client::domain::encounter::check_active_player(const player& player) const
{
    return player.id == active_creature_ptr->id;
}
