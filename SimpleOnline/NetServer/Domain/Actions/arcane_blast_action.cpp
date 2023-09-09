#include "arcane_blast_action.h"

dungeon_server::domain::action::arcane_blast_action::~arcane_blast_action() = default;

std::string dungeon_server::domain::action::arcane_blast_action::get_name()
{
    return "arcane blast";
}

std::uint8_t dungeon_server::domain::action::arcane_blast_action::get_targets_count()
{
    return 1;
}

void dungeon_server::domain::action::arcane_blast_action::use(const std::shared_ptr<encounter>& encounter_ptr, std::string& action_log)
{
    
}
