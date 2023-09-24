#include "goblin_warrior.h"

#include "NetServer/Domain/Actions/distracting_slash_action.h"
#include "NetServer/Domain/Actions/sword_slash_action.h"
#include "NetServer/Utility/randomizer.h"

dungeon_server::domain::enemy::goblin_warrior::goblin_warrior(uint16_t health, uint16_t attack_damage, uint16_t ability_power)
    : base_enemy(health, attack_damage, ability_power, dungeon_common::enums::elemental_property_type::normal)
{
}

std::string dungeon_server::domain::enemy::goblin_warrior::get_base_name()
{
    return "goblin warrior";
}

void dungeon_server::domain::enemy::goblin_warrior::on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, dungeon_server::domain::action_log& action_log)
{
    const auto target = get_random_player(encounter_ptr);
    const auto percentage = utility::randomizer::randomize(0, 100);
    std::shared_ptr<action::base_action> action;

    if (percentage <= 80)
    {
        action = std::make_shared<action::distracting_slash_action>(dungeon_common::model::action_types::distracting_slash,
                                                                    public_id, target->public_id);
    }
    else
    {
        action = std::make_shared<action::sword_slash_action>(dungeon_common::model::action_types::distracting_slash,
                                                              public_id, target->public_id);
    }

    action->use(encounter_ptr, action_log);
}
