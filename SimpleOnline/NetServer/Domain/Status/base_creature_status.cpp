#include "base_creature_status.h"


dungeon_server::domain::base_creature_status::base_creature_status(const dungeon_common::enums::creature_status_type status_type, const uint8_t quantity,
                                                                           std::string creature_id)
                                                                           : creature_id_(std::move(creature_id)),
                                                                            status_type(status_type),
                                                                            quantity(quantity)
{
}
