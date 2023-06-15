#pragma once

namespace dungeon_server::domain
    {
        class base_creature
        {
        public:
            std::string name;
            uint16_t health;
            uint16_t damage;
            std::string public_id;
            
            virtual ~base_creature()
            {                
            }

            base_creature(std::string name, const uint16_t health, const uint16_t damage) : name(std::move(name)), health(health), damage(damage)
            {
            }
            
            void take_damage(const int dmg)
            {
                health -= dmg;
            }
        };
    }
