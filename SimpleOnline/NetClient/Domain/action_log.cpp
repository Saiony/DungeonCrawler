#include "action_log.h"

std::list<std::string> dungeon_client::domain::action_log::get_log()
{
    return log_;
}