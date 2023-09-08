#pragma once

#include <string>
#include <vector>
#include "base_creature.h"
#include "player_classes.h"
#include "Message/emitter_message.h"
#include "Models/action_use_model.h"

namespace dungeon_server::domain
{    
    class player final : public base_creature
    {
    public:
        std::string private_id;
        std::uint16_t aggro;
        player_class player_class;
        std::vector<dungeon_common::model::action_types> actions;
        
        void do_something() const;
        player(std::string client_id, const std::string& new_name, domain::player_class player_class, uint16_t new_health, uint16_t new_damage,
               uint16_t new_ability_power, std::vector<dungeon_common::model::action_types> actions,
               dungeon_common::enums::elemental_property_type elemental_property);
    };
}
