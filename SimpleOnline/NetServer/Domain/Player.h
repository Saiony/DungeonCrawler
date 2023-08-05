#pragma once

#include <string>
#include <vector>
#include "base_creature.h"
#include "Models/action_use_model.h"

namespace dungeon_server::domain
{
    class player final : public base_creature
    {
    public:
        std::string private_id;
        std::vector<dungeon_common::model::action_types> actions;
        
        void do_something() const;
        player(std::string client_id, const std::string& new_name, const uint16_t new_health, const uint16_t new_damage,
               const uint16_t new_ability_power, std::vector<dungeon_common::model::action_types> actions);
    };

    enum class_type
    {
        unknown = 0,
        warrior = 1,
    };
}
