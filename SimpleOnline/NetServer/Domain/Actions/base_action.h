#pragma once
#include <iostream>
#include "Models/action_use_model.h"
#include "NetServer/Domain/Encounter.h"

namespace dungeon_server::domain::action
{
    class base_action
    {
    public:
        virtual ~base_action();
        dungeon_common::model::action_types id;
        std::string action_owner_id{};
        float_t variance{};

        explicit base_action(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id);

        virtual std::string get_name()
        {
            return "unknown";
        }

        virtual std::uint8_t get_targets_count()
        {
            return -1;
        }

        virtual std::string use(const std::shared_ptr<encounter>& encounter_ptr)
        {
            return "default log";
        }

        std::shared_ptr<base_creature> get_creature(const std::shared_ptr<encounter>& encounter_ptr, const std::string& creature_id);
        float_t randomize_damage(float_t damage, float_t damage_variance) const;
    };
}
