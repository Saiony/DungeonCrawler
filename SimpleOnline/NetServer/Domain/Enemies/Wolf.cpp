#include "Wolf.h"

#include "NetServer/Domain/Actions/bite_action.h"

dungeon_server::domain::enemy::wolf::wolf(const std::string& new_name, const uint16_t new_health, const uint16_t new_damage, const uint16_t new_ability_power)
                                        : base_enemy(new_name, new_health, new_damage, new_ability_power)
{
}

void dungeon_server::domain::enemy::wolf::on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{    
    const auto target = get_random_player(encounter_ptr);
    action::bite_action action(dungeon_common::model::action_types::bite, public_id, target->public_id);
    action_log += action.use(encounter_ptr);
}
