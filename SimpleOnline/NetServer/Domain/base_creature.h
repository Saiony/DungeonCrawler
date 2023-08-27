#pragma once

#include <memory>
#include <string>

#include "Status/creature_status_manager.h"

namespace dungeon_server::domain
{
    class encounter;
    class creature_status_manager;
    class base_creature_status;

    class base_creature
    {
    protected:
        std::shared_ptr<creature_status_manager> status_manager_;
    public:
        std::string public_id;
        std::string name;
        uint16_t health;
        uint16_t max_health;
        uint16_t attack_damage;
        uint16_t ability_power;
        bool alive;

        virtual ~base_creature();

        base_creature(std::string name, const uint16_t health, const uint16_t damage, const uint16_t ability_power)
            : name(std::move(name)), health(health), max_health(health), attack_damage(damage), ability_power(ability_power), alive(true)
        {
            status_manager_ = std::make_shared<creature_status_manager>();
        }

        void take_damage(const int dmg, std::string& log)
        {
            std::string additional_log;

            if (health - dmg <= 0)
            {
                health = 0;
                alive = false;
                additional_log += "\n" + name + " died!";
            }
            else
                health -= dmg;

            log += "\n" + name + " lost " + std::to_string(dmg) + " hp" + additional_log;
        }

        int heal(const int value)
        {
            auto hp_increased = value;
            health += value;

            if (health > max_health)
            {
                hp_increased = max_health - (health - value);
                health = max_health;
            }

            return hp_increased;
        }

        void add_status(const std::shared_ptr<base_creature_status>& status)
        {
            status_manager_->add_status(status);
        }

        void on_begin_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log)
        {
            status_manager_->on_begin_of_turn(encounter, action_log);
        }

        void on_end_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log)
        {
            status_manager_->on_end_of_turn(encounter, action_log);
        }

        bool can_execute_turn()
        {
            return !status_manager_->contains(dungeon_common::enums::stun);
        }
    };

    inline base_creature::~base_creature() = default;
}
