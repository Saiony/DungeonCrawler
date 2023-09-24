#pragma once
#include <list>
#include <string>

namespace dungeon_client::domain
{
    class action_log
    {
    private:
        std::list<std::string> log_; 
    public:
        std::list<std::string> get_log();
    };
}