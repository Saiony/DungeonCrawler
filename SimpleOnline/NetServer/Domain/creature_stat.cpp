#include "creature_stat.h"

creature_stat::creature_stat() = default;

creature_stat::creature_stat(const dungeon_common::enums::creature_stat_types id, std::string name)
    : id(id), name(std::move(name))
{
}
