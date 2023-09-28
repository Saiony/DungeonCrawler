#include "encounter.h"

#include "../Scenes/CharacterCreationScene.h"
#include "../Utility/string_utility.h"

dungeon_client::domain::encounter::encounter(std::vector<enemy> enemies, std::vector<player> players, const std::string& active_creature_id,
                                             const std::list<std::string>& log, const bool combat_ended)
                                             :
                                             enemies(std::move(enemies)), players(std::move(players)), log(log),
                                             combat_ended(combat_ended)
{
    std::ranges::for_each(this->players, [&](auto player)
    {
        creatures.push_back(std::make_shared<base_creature>(player));
    });

    std::ranges::for_each(this->enemies, [&](auto enemy)
    {
        creatures.push_back(std::make_shared<base_creature>(enemy));
    });

    const auto active_creature_it = std::ranges::find_if(this->creatures, [&active_creature_id](auto creature)
    {
        return creature->public_id == active_creature_id;
    });

    if (active_creature_it != std::end(this->creatures))
    {
        active_creature_ptr = *active_creature_it;
        return;
    }    
}

bool dungeon_client::domain::encounter::check_active_player(const player& player) const
{
    return player.public_id == active_creature_ptr->public_id;
}

std::shared_ptr<dungeon_client::domain::base_creature> dungeon_client::domain::encounter::get_creature(const std::string& creature_name)
{
    const auto creature_it = std::ranges::find_if(creatures, [&creature_name](auto creature)
    {
        return utility::string_utility::compare_string(creature->name, creature_name);
    });

    return creature_it != std::end(creatures) ? *creature_it : nullptr;
}
