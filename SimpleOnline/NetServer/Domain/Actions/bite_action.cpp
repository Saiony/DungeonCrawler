﻿#include "bite_action.h"

#include "NetServer/Domain/Status/stunned_status.h"

dungeon_server::domain::action::bite_action::~bite_action()
{
}

dungeon_server::domain::action::bite_action::bite_action(const dungeon_common::model::action_types& action_type,
                                                         const std::string& new_action_owner_id, std::string target_id)
                                                        : base_action(action_type, new_action_owner_id), target_id_(std::move(target_id))
{
}

dungeon_server::enums::offensive_stats_type dungeon_server::domain::action::bite_action::get_offensive_stat_type()
{
    return enums::offensive_stats_type::attack_damage;
}

float_t dungeon_server::domain::action::bite_action::get_damage_variance()
{
    return 0.2f;
}

float_t dungeon_server::domain::action::bite_action::get_offensive_stat_multiplier()
{
    return 1;
}

std::string dungeon_server::domain::action::bite_action::get_name()
{
    return "bite";
}

void dungeon_server::domain::action::bite_action::use(const std::shared_ptr<encounter>& encounter_ptr, action_log& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    action_log.add_log(action_owner->name + " used " + get_name() +" on " +target->name);
    
    const auto damage = calculate_final_attack(encounter_ptr);
    target->take_damage(damage, action_log, encounter_ptr, action_owner_id);
    action_owner->on_attack(encounter_ptr, target_id_, action_log);
}