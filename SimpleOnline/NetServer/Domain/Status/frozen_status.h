#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class base_creature;

    class frozen_status final : public base_creature_status
    {
    private:
        void end_status(const std::shared_ptr<encounter>& encounter);
    public:
        explicit frozen_status(const std::string& creature_id, const std::shared_ptr<base_creature>& creature);
        dungeon_common::enums::creature_status_type get_type() override;
        
        void on_begin_of_turn(const std::shared_ptr<encounter>& encounter, action_log& action_log) override;
        void on_end_of_turn(const std::shared_ptr<encounter>& encounter, action_log& action_log) override;
        void on_overriding_status_added(std::shared_ptr<base_creature_status> status) override;
        void on_attacked(const std::shared_ptr<encounter>& encounter, action_log& action_log,
                         const std::string& attacker_id, uint16_t damage,
                         dungeon_common::enums::elemental_property_type) override;
        ~frozen_status() override;
    };
}
