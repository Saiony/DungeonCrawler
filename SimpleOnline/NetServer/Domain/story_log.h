#pragma once
#include <list>
#include <string>

namespace dungeon_server::domain
{
    class story_log
    {
    private:
        std::list<std::string> log_; 
    public:
        void add_log(const std::string& log);
        std::list<std::string> get_log();
    };
}
