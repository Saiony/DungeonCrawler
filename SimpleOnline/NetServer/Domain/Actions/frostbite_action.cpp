#include "frostbite_action.h"

dungeon_server::domain::action::frostbite_action::~frostbite_action() = default;

std::string dungeon_server::domain::action::frostbite_action::get_name()
{
    return "frostbite";
}

std::uint8_t dungeon_server::domain::action::frostbite_action::get_targets_count()
{
    return 1;
}

void dungeon_server::domain::action::frostbite_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    
}