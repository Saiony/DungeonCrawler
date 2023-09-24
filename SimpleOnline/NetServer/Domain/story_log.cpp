#include "story_log.h"
#include <iostream>

void dungeon_server::domain::story_log::add_log(const std::string& log)
{
    log_.push_back(log);
    std::cout << "\n" + log; 
}

std::list<std::string> dungeon_server::domain::story_log::get_log()
{
    return log_;
}