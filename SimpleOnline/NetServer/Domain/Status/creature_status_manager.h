#pragma once

#include <memory>
#include <string>
#include <vector>
#include "creature_status_manager.h"
#include "base_creature_status.h"
#include "Enum/creature_status_types.h"

namespace dungeon_server::domain
{
    class encounter;
    class base_creature_status;

    class creature_status_manager
    {
    private:
        std::vector<std::shared_ptr<base_creature_status>> statuses_{};
    public:
        void add_status(const std::shared_ptr<base_creature_status>& status);
        bool contains(dungeon_common::enums::creature_status_type status_type);
        void on_begin_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log);
        void on_attack(std::shared_ptr<encounter> encounter, const std::string& attacked_creature_id, std::string& action_log);
        void on_end_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log);
    };
}
