#include "eagle_petted_status.h"

#include "NetServer/Domain/Encounter.h"

dungeon_server::domain::eagle_petted_status::eagle_petted_status(const dungeon_common::enums::creature_status_type status_type, const uint8_t quantity, const std::string& creature_id)
                                                   : base_creature_status(status_type, quantity, creature_id)
{
}

void dungeon_server::domain::eagle_petted_status::on_attack(std::shared_ptr<encounter> encounter, const std::string& attacked_creature_id, std::string& action_log)
{
    const auto attacked_creature = encounter->get_creature(attacked_creature_id);
    action_log += "\nEagle attacked " + attacked_creature->name;

    const auto damage = 1;
    attacked_creature->take_damage(damage, action_log);
}

void dungeon_server::domain::eagle_petted_status::on_end_of_turn(std::shared_ptr<encounter> encounter, std::string& action_log)
{
    quantity--;

    if(quantity <= 0)
        action_log += "\nEagle does not feel cared anymore";
}
