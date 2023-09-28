#pragma once
#include <list>
#include <string>

namespace dungeon_client::domain
{
    class story
    {
    private:        
        std::list<std::string> log_;
    public:
        explicit story(std::list<std::string> log);
        std::list<std::string> get_log();
    };
}
