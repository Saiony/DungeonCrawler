#pragma once
#include "Models/action_use_model.h"
#include "NetServer/Domain/action_log.h"
#include "NetServer/Domain/Encounter.h"
#include "NetServer/Enum/offensive_stats_type.h"

namespace dungeon_server::domain::action
{
    class base_action
    {
    public:
        virtual ~base_action();
        dungeon_common::model::action_types id;
        std::string action_owner_id{};

        explicit base_action(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id);

        virtual std::string get_name()
        {
            return "unknown";
        }

        virtual enums::offensive_stats_type get_offensive_stat_type()
        {
            return enums::offensive_stats_type::unknown;
        }

        virtual std::uint8_t get_targets_count()
        {
            return -1;
        }

        virtual float_t get_damage_variance()
        {
            return -1;
        }

        virtual float_t get_offensive_stat_multiplier()
        {
            return -1;
        }

        virtual void use(const std::shared_ptr<encounter>& encounter_ptr, action_log& action_log)
        {
        }

        float_t randomize_damage(float_t damage, float_t damage_variance) const;
        uint16_t calculate_final_attack(const std::shared_ptr<encounter>& encounter_ptr);
    };
}
