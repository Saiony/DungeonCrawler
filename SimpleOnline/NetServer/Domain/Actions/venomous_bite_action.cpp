﻿#include "venomous_bite_action.h"
#include "NetServer/Domain/Status/poisoned_status.h"

dungeon_server::domain::action::venomous_bite_action::~venomous_bite_action() = default;

dungeon_server::domain::action::venomous_bite_action::venomous_bite_action(const dungeon_common::model::action_types& action_type,
                                                                           std::string new_action_owner_id,
                                                                           std::string target_id)
    : base_action(action_type, std::move(new_action_owner_id)), target_id_(std::move(target_id))
{
}

std::string dungeon_server::domain::action::venomous_bite_action::get_name()
{
    return "venomous bite";
}

dungeon_server::enums::offensive_stats_type dungeon_server::domain::action::venomous_bite_action::get_offensive_stat_type()
{
    return enums::offensive_stats_type::attack_damage;
}

float_t dungeon_server::domain::action::venomous_bite_action::get_damage_variance()
{
    return 0.2f;
}

float_t dungeon_server::domain::action::venomous_bite_action::get_offensive_stat_multiplier()
{
    return 0.5f;
}

void dungeon_server::domain::action::venomous_bite_action::use(const std::shared_ptr<encounter>& encounter_ptr, action_log& action_log)
{
    const auto action_owner = encounter_ptr->get_creature(action_owner_id);
    const auto target = encounter_ptr->get_creature(target_id_);
    action_log.add_log(action_owner->name + " used " + get_name() + " on " + target->name);

    const auto damage = calculate_final_attack(encounter_ptr);
    target->take_damage(damage, action_log, encounter_ptr, action_owner_id, dungeon_common::enums::elemental_property_type::normal);

    const auto status = target->add_status(std::make_shared<poisoned_status>(target->public_id));
    action_log.add_log(target->name + " is poisoned [" + std::to_string(status->quantity) + "]");

    action_owner->on_attack(encounter_ptr, target_id_, action_log);
}
