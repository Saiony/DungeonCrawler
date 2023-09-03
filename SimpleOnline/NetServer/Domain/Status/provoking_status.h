#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class provoking_status : public base_creature_status
    {
    private:
        const uint8_t aggro_increase_ = 5;
        
    public:
        provoking_status(const std::string& creature_id, const std::shared_ptr<encounter>& encounter_ptr);
        
        dungeon_common::enums::creature_status_type get_type() override;        
        void on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log) override;
    };
}
