#include "weakness_util.h"

#include <string>

int dungeon_server::utility::weakness_util::get_attack_multiplier(const dungeon_common::enums::elemental_property_type attack_type,
                                                            const dungeon_common::enums::elemental_property_type target_type)
{
    const auto target_weakness = targets_weakness.find(target_type);

    if(target_weakness == std::end(targets_weakness))
        throw std::exception("Invalid attack type");
  
    const auto attack_multiplier = target_weakness->second.find(attack_type);

    if(attack_multiplier == std::end(target_weakness->second))
        return 1;

    return attack_multiplier->second / 100;
}
