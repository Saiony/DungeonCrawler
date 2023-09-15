#include "base_creature_status.h"


dungeon_server::domain::base_creature_status::base_creature_status(std::string creature_id, const uint8_t quantity)
    : creature_id_(std::move(creature_id)),
      quantity(quantity)
{
}

void dungeon_server::domain::base_creature_status::add_on_end_listener(std::function<void(const std::shared_ptr<base_creature_status>&)> callback)
{
    end_status_ = std::move(callback);
}
