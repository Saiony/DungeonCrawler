﻿#pragma once
#include <cstdint>
#include <iostream>

#include "Enum/creature_status_types.h"

namespace dungeon_server::domain
{
    class encounter;

    class base_creature_status
    {
    protected:
        std::string creature_id_;
    public:
        uint8_t quantity;

        base_creature_status(std::string creature_id, const uint8_t quantity);

        virtual dungeon_common::enums::creature_status_type get_type() = 0;
        
        virtual void on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
        {
        }

        virtual int16_t get_attack_multiplier()
        {
            return -1;
        }

        virtual void on_after_attack(const std::shared_ptr<encounter>& encounter, const std::string& attacked_creature_id, std::string& action_log)
        {
        }
        
        virtual void on_end_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log)
        {
        }

        virtual void on_overriding_status_added(std::shared_ptr<base_creature_status> status) = 0;
    };
}
