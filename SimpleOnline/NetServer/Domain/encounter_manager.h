﻿#pragma once
#include <cstdint>
#include <functional>
#include <vector>

#include "Encounter.h"

namespace dungeon_server::domain
{
    class encounter_manager
    {
    private:
        const uint8_t max_level_ = 3;
        std::vector<std::shared_ptr<player>> players_;

        std::shared_ptr<encounter> generate_encounter(const uint8_t level) const;    
    public:
        std::shared_ptr<encounter> current_encounter{};

        explicit encounter_manager(std::vector<std::shared_ptr<player>> players);
        bool go_to_next_turn(action_log& action_log) const;
        void start_encounter(uint8_t level);
    };
}
