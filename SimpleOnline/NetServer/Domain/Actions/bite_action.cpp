#include "bite_action.h"

dungeon_server::domain::action::bite_action::~bite_action()
{
}

dungeon_server::domain::action::bite_action::bite_action(const dungeon_common::model::action_types& action_type, std::string target_id)
                                                        : base_action(action_type), target_id(std::move(target_id))
{
}

void dungeon_server::domain::action::bite_action::use(const std::shared_ptr<encounter>& encounter_ptr)
{
    const auto target_it = std::ranges::find_if(encounter_ptr->creatures, [this](auto enemy)
       {
           return enemy->public_id == target_id;
       });

    const auto target = *target_it;
    std::cout << "[BITE] on " << target->name << std::endl;
    target->take_damage(5);
}
