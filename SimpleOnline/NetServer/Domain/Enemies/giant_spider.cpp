#include "giant_spider.h"

#include "spider.h"
#include "NetServer/Domain/Actions/base_action.h"
#include "NetServer/Domain/Actions/silk_prison_action.h"
#include "NetServer/Domain/Actions/venomous_bite_action.h"
#include "NetServer/Utility/randomizer.h"

dungeon_server::domain::enemy::giant_spider::giant_spider(const uint16_t health,
                                                          const uint16_t attack_damage, const uint16_t ability_power)
    : base_enemy(health, attack_damage, ability_power,
                 dungeon_common::enums::elemental_property_type::earth)
{
}

void dungeon_server::domain::enemy::giant_spider::on_execute_turn(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    const auto target = get_random_player(encounter_ptr);
    const auto percentage = utility::randomizer::randomize(0, 100);
    std::shared_ptr<action::base_action> action;

    if (percentage <= 50)
    {
        action = std::make_shared<action::venomous_bite_action>(dungeon_common::model::action_types::venomous_bite,
                                                                public_id, target->public_id);
    }
    else
    {
        action = std::make_shared<action::silk_prison_action>(dungeon_common::model::action_types::silk_prison,
                                                              public_id, target->public_id);
    }

    action->use(encounter_ptr, action_log);
}


void dungeon_server::domain::enemy::giant_spider::on_died(const std::shared_ptr<encounter>& encounter, std::string& action_log)
{
    action_log += "\nThe " + name + " dies... But newborn spiders start crawling from her back...";
    for (int i = 1; i <= 3; ++i)
    {
        encounter->add_enemy(std::make_shared<spider>(7, 3, 1));
    }
}

std::string dungeon_server::domain::enemy::giant_spider::get_base_name()
{
    return "giant spider";
}
