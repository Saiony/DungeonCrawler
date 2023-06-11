#pragma once
#include <string>

namespace dungeon_client::domain
{
    class base_creature
    {
    private:
        std::string id_;
        std::string name_;
        uint16_t health_{};
    public:
        base_creature() = default;

        base_creature(std::string id, std::string name, const uint16_t health) : id_(std::move(id)), name_(std::move(name)), health_(health)
        {
        }

        std::string get_name()
        {
            return name_;
        }
        
        std::string get_id()
        {
            return id_;
        }
        
        uint16_t get_health() const
        {
            return health_;
        }
    };
}
