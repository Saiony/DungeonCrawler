#include "Wolf.h"

#include "NetServer/Domain/Actions/bite_action.h"

dungeon_server::domain::enemy::wolf::wolf(const std::string& name, uint16_t health, uint16_t attack_damage, uint16_t ability_power,
                                          dungeon_common::enums::elemental_property_type elemental_property)
                                          : base_enemy(name, health, attack_damage, ability_power, elemental_property)  
{
}
void dungeon_server::domain::enemy::wolf::on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{    
    const auto target = get_random_player(encounter_ptr);
    action::bite_action action(dungeon_common::model::action_types::bite, public_id, target->public_id);
    action_log += action.use(encounter_ptr);
}

