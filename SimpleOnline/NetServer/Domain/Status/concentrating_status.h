﻿#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class concentrating_status : public base_creature_status
    {
    public:
        explicit concentrating_status(const std::string& creature_id);

        dungeon_common::enums::creature_status_type get_type() override;
        void on_after_attack(const std::shared_ptr<encounter>& encounter, const std::string& attacked_creature_id, action_log& action_log) override;
        int16_t get_attack_multiplier() override;
        void on_overriding_status_added(std::shared_ptr<base_creature_status> status) override;
    };
}