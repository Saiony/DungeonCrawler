#pragma once

#include <memory>
#include <string>

#include "../Utility/weakness_util.h"
#include "Enum/elemental_property_type.h"
#include "Status/creature_status_manager.h"

namespace dungeon_server::domain
{
    class encounter;
    class creature_status_manager;

    class base_creature
    {
    private:
        dungeon_common::enums::elemental_property_type original_elemental_property_;
    protected:
        std::shared_ptr<creature_status_manager> status_manager_;
    public:
        std::string public_id;
        std::string name;
        uint16_t health;
        uint16_t max_health;
        uint16_t attack_damage;
        uint16_t ability_power;
        dungeon_common::enums::elemental_property_type elemental_property;
        bool alive;

        virtual ~base_creature();

        base_creature(std::string name, const uint16_t health, const uint16_t damage, const uint16_t ability_power,
                      const dungeon_common::enums::elemental_property_type elemental_property)
                      : name(std::move(name)), health(health), max_health(health), attack_damage(damage), ability_power(ability_power),
                      elemental_property(elemental_property), alive(true)
        {
            status_manager_ = std::make_shared<creature_status_manager>();
            original_elemental_property_ = elemental_property;
        }

        void take_damage(const int dmg, std::string& log, const std::shared_ptr<encounter>& encounter,
                         const std::string& attacker_id = nullptr,
                         const dungeon_common::enums::elemental_property_type attack_property = dungeon_common::enums::elemental_property_type::normal)
        {
            std::string additional_log;
            const auto dmg_multiplier = utility::weakness_util::get_attack_multiplier(attack_property, elemental_property);
            const auto final_dmg = dmg * dmg_multiplier;

            if (health - final_dmg <= 0)
            {
                health = 0;
                alive = false;
                additional_log += "\n" + name + " died!";
            }
            
            health -= final_dmg;
            log += "\n" + name + " lost " + std::to_string(final_dmg) + " hp" + additional_log;
            on_attacked(encounter, log, attacker_id, dmg, attack_property);
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

        std::shared_ptr<base_creature_status> add_status(const std::shared_ptr<base_creature_status>& status) const
        {
            return status_manager_->add_status(status);
        }

        void on_begin_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log) const
        {
            status_manager_->on_begin_of_turn(encounter, action_log);
        }

        void on_attack(const std::shared_ptr<encounter>& encounter, const std::string& attacked_creature_id, std::string& action_log) const
        {
            status_manager_->on_attack(encounter, attacked_creature_id, action_log);
        }

        void on_attacked(const std::shared_ptr<encounter>& encounter,
                         std::string& action_log, const std::string& attacker_id, const uint16_t damage,
                         const dungeon_common::enums::elemental_property_type attack_property) const
        {
            status_manager_->on_attacked(encounter, action_log, attacker_id, damage, attack_property);
        }

        void on_end_of_turn(const std::shared_ptr<encounter>& encounter, std::string& action_log) const
        {
            status_manager_->on_end_of_turn(encounter, action_log);
        }

        bool can_execute_turn() const
        {
            return !(status_manager_->contains(dungeon_common::enums::creature_status_type::stun) ||
                     status_manager_->contains(dungeon_common::enums::creature_status_type::frozen));
        }

        uint16_t get_attack_multipliers() const
        {
            return status_manager_->get_attack_multipliers();
        }

        void change_elemental_property(const dungeon_common::enums::elemental_property_type new_property)
        {
            if(new_property == dungeon_common::enums::elemental_property_type::unknown)
                throw std::exception("Invalid elemental property");

            elemental_property = new_property;
        }

        void set_original_elemental_property()
        {
            elemental_property = original_elemental_property_;
        }
    };

    inline base_creature::~base_creature() = default;
}
