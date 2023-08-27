#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class stunned_status : public base_creature_status
    {
    public:
        stunned_status(dungeon_common::enums::creature_status_type status_type, uint8_t quantity, const std::string& creature_id);
        void on_begin_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log) override;
        void on_end_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log) override;
    };
}
