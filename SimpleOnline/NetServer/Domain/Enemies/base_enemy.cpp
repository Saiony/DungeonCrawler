#include "base_enemy.h"

#include <random>

#include "NetServer/Domain/Encounter.h"
#include "Utility/guid_generator.h"

dungeon_server::domain::base_enemy::base_enemy(const std::string& name, const uint16_t health, const uint16_t attack_damage, const uint16_t ability_power)
                        : base_creature(name, health, attack_damage, ability_power) 
{
    public_id = dungeon_common::utility::guid_generator::create_guid();
}

std::shared_ptr<dungeon_server::domain::player> dungeon_server::domain::base_enemy::get_random_player(const std::shared_ptr<encounter>& encounter_ptr) const
{
    std::mt19937 gen(std::random_device{}());
    std::vector<double> aggro;
    
    std::ranges::for_each(encounter_ptr->players, [&aggro](auto player)
    {
        aggro.push_back(player->aggro);
    });
    
    std::discrete_distribution<std::size_t> distribution{std::begin(aggro), std::end(aggro)};
    return encounter_ptr->players[distribution(gen)];
}




