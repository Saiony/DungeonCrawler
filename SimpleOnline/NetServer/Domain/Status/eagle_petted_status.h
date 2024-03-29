﻿#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class eagle_petted_status : public base_creature_status
    {
    private:
        const uint16_t damage_ = 1;
    public:
        explicit eagle_petted_status(const std::string& creature_id);
        
        dungeon_common::enums::creature_status_type get_type() override;
        void on_after_attack(const std::shared_ptr<encounter>& encounter, const std::string& attacked_creature_id, action_log& action_log) override;
        void on_end_of_turn(const std::shared_ptr<encounter>& encounter, action_log& action_log) override;
        void on_overriding_status_added(std::shared_ptr<base_creature_status> status) override;
    };
}
