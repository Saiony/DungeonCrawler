#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class stunned_status : public base_creature_status
    {
    public:
        explicit stunned_status(const std::string& creature_id);
        dungeon_common::enums::creature_status_type get_type() override;
        
        void on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log) override;
        void on_end_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log) override;
        void on_overriding_status_added(std::shared_ptr<base_creature_status> status) override;
    };
}
