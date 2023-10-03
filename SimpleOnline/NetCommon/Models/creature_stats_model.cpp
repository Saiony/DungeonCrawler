#include "creature_stats_model.h"

creature_stats_model::creature_stats_model() = default;

creature_stats_model::creature_stats_model(const dungeon_common::enums::creature_stat_types id, std::string name_string): id(id)
{
    std::copy(std::begin(name_string), std::end(name_string), name);
}
