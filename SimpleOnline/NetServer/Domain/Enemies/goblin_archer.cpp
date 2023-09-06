#include "goblin_archer.h"

#include "NetServer/Domain/Actions/arrow_shot_action.h"
#include "NetServer/Utility/randomizer.h"
#include "NetServer/Domain/Actions/arrow_shower_action.h"

dungeon_server::domain::enemy::goblin_archer::goblin_archer(const std::string& name, const uint16_t health,
                                                            const uint16_t attack_damage, const uint16_t ability_power)
                                                              : base_enemy(name, health, attack_damage, ability_power)
{
}

void dungeon_server::domain::enemy::goblin_archer::on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto target = get_random_player(encounter_ptr);
    const auto percentage = utility::randomizer::randomize(0, 100);
    std::shared_ptr<action::base_action> action;
    
    if(percentage <= 30)
    {
        action = std::make_shared<action::arrow_shower_action>(dungeon_common::model::action_types::arrow_shower, public_id,
                                                                dungeon_common::enums::action_target_types::all_players);
    }
    else
    {
        action = std::make_shared<action::arrow_shot_action>(dungeon_common::model::action_types::arrow_shot,
                                                    public_id, target->public_id);
    }
    
    action_log += action->use(encounter_ptr);
}
