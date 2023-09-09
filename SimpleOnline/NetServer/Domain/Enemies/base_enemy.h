#pragma once
#include <string>

#include "Enum/elemental_property_type.h"
#include "NetServer/Domain/base_creature.h"
#include "NetServer/Domain/player.h"

namespace dungeon_server::domain
{
    class encounter;
    
    class base_enemy : public base_creature
    {
    protected:
        virtual void on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log) = 0;
    public:
        base_enemy(const std::string& name, uint16_t health, uint16_t attack_damage, uint16_t ability_power,
                   dungeon_common::enums::elemental_property_type elemental_property);
        
        void execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
        {            
            if(!can_execute_turn())
                return;
            
            on_execute_turn(encounter_ptr, action_log);
        }

        std::shared_ptr<player> get_random_player(const std::shared_ptr<encounter>& encounter_ptr) const;
    };
}
