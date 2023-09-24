#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class poisoned_status final : public base_creature_status
    {
    private:
        uint16_t damage_ = 1;
    public:
        poisoned_status(const std::string& creature_id);

        dungeon_common::enums::creature_status_type get_type() override;
        void on_overriding_status_added(std::shared_ptr<base_creature_status> status) override;
        void on_begin_of_turn(const std::shared_ptr<encounter>& encounter, action_log& action_log) override;
    };
}
