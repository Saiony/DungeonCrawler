#include "bite_action.h"

dungeon_server::domain::action::bite_action::~bite_action()
{
}

dungeon_server::domain::action::bite_action::bite_action(const dungeon_common::model::action_types& action_type,
                                                        std::string new_action_owner_id, std::string target_id)
                                                        : base_action(action_type, new_action_owner_id), target_id(std::move(target_id))
{
}

std::string dungeon_server::domain::action::bite_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto action_owner = get_creature(encounter_ptr, action_owner_id);
    const auto target = get_creature(encounter_ptr, target_id);
    const auto dmg_taken = target->take_damage(action_owner->damage);

    //log
    std::string log = action_owner->name + " used " + get_name() +" on " +target->name +"\n" +target->name + " lost " +std::to_string(dmg_taken) +" hp";
    std::cout << "[BITE] on " << target->name << std::endl;
    return log;
}

std::string dungeon_server::domain::action::bite_action::get_name()
{
    return "bite";
}
