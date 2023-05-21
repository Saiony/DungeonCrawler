#pragma once
#include <string>

namespace dungeon_server::domain::enemy
{
    class base_enemy
    {
    protected:
        std::string id_;
        std::string name_;
        uint16_t health_;
        uint16_t damage_;

    public:
        base_enemy(std::string name, const uint16_t health, const uint16_t damage);
        virtual void execute_turn();
        std::string get_name() const;
        uint16_t get_health() const;
        std::string get_id() const;
    };
}
