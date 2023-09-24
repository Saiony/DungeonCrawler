#pragma once

#include <map>
#include <memory>
#include <string>
#include "creature_status_manager.h"
#include "base_creature_status.h"
#include "elemental_property_type.h"
#include "Enum/creature_status_types.h"
#include "../action_log.h"

namespace dungeon_server::domain
{
    class encounter;
    class base_creature_status;

    class creature_status_manager
    {
    private:
        std::map<dungeon_common::enums::creature_status_type, std::shared_ptr<base_creature_status>> statuses_{};

    public:
        std::shared_ptr<base_creature_status> add_status(const std::shared_ptr<base_creature_status>& status);
        bool contains(dungeon_common::enums::creature_status_type status_type) const;
        uint16_t get_attack_multipliers();
        void on_begin_of_turn(std::shared_ptr<encounter> encounter, action_log& action_log);
        void on_attack(std::shared_ptr<encounter> encounter, const std::string& attacked_creature_id, action_log& action_log);
        void on_attacked(const std::shared_ptr<encounter>& encounter, action_log& action_log, const std::string& attacker_id,
                         uint16_t damage, dungeon_common::enums::elemental_property_type elemental_property);
        void on_end_of_turn(std::shared_ptr<encounter> encounter, action_log& action_log);
    };
}
