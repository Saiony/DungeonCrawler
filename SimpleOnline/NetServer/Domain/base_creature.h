#pragma once

namespace dungeon_server::domain
    {
        class base_creature
        {
        public:
            std::string public_id;
            std::string name;
            uint16_t health;
            uint16_t max_health;
            uint16_t attack_damage;
            uint16_t ability_power;
            bool alive;
            
            virtual ~base_creature()
            {                
            }

            base_creature(std::string name, const uint16_t health, const uint16_t damage, const uint16_t ability_power)
                            : name(std::move(name)), health(health), max_health(health), attack_damage(damage), ability_power(ability_power), alive(true)
            {
            }
            
            void take_damage(const int dmg, std::string& log)
            {
                std::string additional_log;
                
                if(health - dmg <= 0)
                {
                    health = 0;
                    alive = false;
                    additional_log += "\n" +name + " died!";
                }
                else
                    health -= dmg;

                log += "\n" +name + " lost " +std::to_string(dmg) +" hp" + additional_log;
            }

            int heal(const int value)
            {
                auto hp_increased = value;
                health += value;

                if(health > max_health)
                {
                    hp_increased = max_health - (health - value);
                    health = max_health;
                }

                return hp_increased;
            }
        };
    }
