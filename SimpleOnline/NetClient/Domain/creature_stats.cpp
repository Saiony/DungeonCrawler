#include "creature_stats.h"

dungeon_client::domain::creature_stats::creature_stats() = default;

dungeon_client::domain::creature_stats::creature_stats(const dungeon_common::enums::creature_stat_types id, std::string name)
    : id(id), name(std::move(name))
{
}
