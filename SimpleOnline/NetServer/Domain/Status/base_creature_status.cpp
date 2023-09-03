#include "base_creature_status.h"


dungeon_server::domain::base_creature_status::base_creature_status(std::string creature_id, const uint8_t quantity)
                                                                    : creature_id_(std::move(creature_id)), quantity(quantity)
{
}
