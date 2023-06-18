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
    //action
    const auto target_it = std::ranges::find_if(encounter_ptr->creatures, [this](auto enemy)
    {
       return enemy->public_id == target_id;
    });

    const auto target = *target_it;
    auto dmg_taken = target->take_damage(5);

    //log
    const auto action_owner = *std::ranges::find_if(encounter_ptr->creatures, [this](auto enemy)
    {
       return enemy->public_id == action_owner_id;
    });
    std::string log = action_owner->name + " used " + get_name() +" on " +target->name +"\n" +target->name + " lost " +std::to_string(dmg_taken) +" hp";
    return log;
}

std::string dungeon_server::domain::action::bite_action::get_name()
{
    return "bite";
}
