#include "stuck_in_spiders_web_status.h"

#include "NetServer/Domain/Encounter.h"
#include "NetServer/Utility/randomizer.h"

dungeon_server::domain::stuck_in_spiders_web_status::stuck_in_spiders_web_status(const std::string& creature_id)
    : base_creature_status(creature_id, 1)
{
}

dungeon_common::enums::creature_status_type dungeon_server::domain::stuck_in_spiders_web_status::get_type()
{
    return dungeon_common::enums::creature_status_type::stuck_in_spiders_web;
}

void dungeon_server::domain::stuck_in_spiders_web_status::on_overriding_status_added(std::shared_ptr<base_creature_status> status)
{
}

void dungeon_server::domain::stuck_in_spiders_web_status::on_begin_of_turn(const std::shared_ptr<encounter>& encounter, dungeon_server::domain::action_log& action_log)
{
    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });
    action_log.add_log(this_creature->name + " tries to break free from the spider web...");

    const auto str_check = utility::randomizer::randomize(0, 10) + this_creature->get_attack_damage();
    if (str_check <= difficulty_class_)
    {
        action_log.add_log("But the web stays strong");
        return;
    }

    end_status(encounter, action_log);
}

void dungeon_server::domain::stuck_in_spiders_web_status::on_attacked(const std::shared_ptr<encounter>& encounter, dungeon_server::domain::action_log& action_log,
                                                                      const std::string& attacker_id, uint16_t damage,
                                                                      dungeon_common::enums::elemental_property_type elemental_property)
{
    end_status(encounter, action_log);
}


void dungeon_server::domain::stuck_in_spiders_web_status::end_status(const std::shared_ptr<encounter>& encounter, dungeon_server::domain::action_log& action_log)
{
    const auto this_creature = *std::ranges::find_if(encounter->creatures, [this](auto creature)
    {
        return creature->public_id == creature_id_;
    });

    end_status_(std::make_shared<stuck_in_spiders_web_status>(*this));
    action_log.add_log("The web rips and " + this_creature->name + " is no longer restrained");
}
