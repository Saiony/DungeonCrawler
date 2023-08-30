#pragma once
#include <cstdint>
#include <iostream>

#include "creature_status_types.h"

namespace dungeon_server::domain
{
    class encounter;

    class base_creature_status
    {
    protected:
        std::string creature_id_;
    public:
        dungeon_common::enums::creature_status_type status_type;
        uint8_t quantity;

        base_creature_status(dungeon_common::enums::creature_status_type status_type, uint8_t quantity, std::string creature_id);
        
        virtual void on_begin_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log)
        {
        }

        virtual void on_attack(std::shared_ptr<encounter> encounter, const std::string& attacked_creature_id, std::string& action_log)
        {
        }
        
        virtual void on_end_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log)
        {
        }
    };
}
