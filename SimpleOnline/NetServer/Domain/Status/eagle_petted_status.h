#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class eagle_petted_status : public base_creature_status
    {
    public:
        eagle_petted_status(dungeon_common::enums::creature_status_type status_type, uint8_t quantity, const std::string& creature_id);

        void on_attack(std::shared_ptr<encounter> encounter, const std::string& attacked_creature_id, std::string& action_log) override;
        void on_end_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log) override;
    };
}
