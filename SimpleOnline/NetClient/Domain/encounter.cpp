#include "encounter.h"

#include "../Scenes/CharacterCreationScene.h"

dungeon_client::domain::encounter::encounter(std::vector<enemy> enemies, std::vector<player> players, const std::string& active_creature_id, const std::string& log)
    : enemies(std::move(enemies)), players(std::move(players)), log(log)
{
    const auto active_player_it = std::ranges::find_if(this->players, [&active_creature_id](auto player)
    {
        return player.public_id == active_creature_id;
    });

    if (active_player_it != std::end(this->players))
    {
        active_creature_ptr = std::make_unique<base_creature>(*active_player_it);
        return;
    }

    const auto active_enemy_it = std::ranges::find_if(this->enemies, [&active_creature_id](auto enemy)
    {
        return enemy.public_id == active_creature_id;
    });

    if (active_enemy_it != std::end(this->enemies))
    {
        active_creature_ptr = std::make_unique<base_creature>(*active_enemy_it);
        return;
    }
}

bool dungeon_client::domain::encounter::check_active_player(const player& player) const
{
    return player.public_id == active_creature_ptr->public_id;
}
