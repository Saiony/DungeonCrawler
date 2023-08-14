#pragma once
#include <array>
#include <memory>

#include "action.h"
#include "Player.h"

namespace dungeon_client::domain
{
    class player_complete : public player
    {
    public:
        uint16_t attack_damage{};
        uint16_t ability_power{};
        std::array<action, 4> actions;        
        
        player_complete(const std::string& id, const std::string& name, const player_class& player_class,
                        const uint16_t attack_damage, const uint16_t ability_power, uint32_t health, std::array<action, 4> actions);
        std::shared_ptr<action> get_action(dungeon_common::model::action_types action_id);
        std::shared_ptr<action> get_action(std::string action_name);
    };
}
