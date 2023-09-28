#include "story.h"

dungeon_client::domain::story::story(std::list<std::string> log): log_(std::move(log))
{
}

std::list<std::string> dungeon_client::domain::story::get_log()
{
    return log_;
}
