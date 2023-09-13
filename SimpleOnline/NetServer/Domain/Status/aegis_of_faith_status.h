#pragma once
#include "base_creature_status.h"

namespace dungeon_server::domain
{
    class aegis_of_faith_status final : public base_creature_status
    {
    public:
        aegis_of_faith_status(const std::string& creature_id, uint8_t quantity);

        dungeon_common::enums::creature_status_type get_type() override;
        void on_overriding_status_added(std::shared_ptr<base_creature_status> status) override;
        ~aegis_of_faith_status() override;
    };
}
