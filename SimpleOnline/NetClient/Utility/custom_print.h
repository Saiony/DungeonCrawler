#pragma once

namespace dungeon_client::utility
{
    class custom_print
    {
    public:        
        template<typename T> static void print_aligned(T text, const int& width)
        {
            std::cout << std::left << std::setw(width) << std::setfill(' ') << text;
        }
    };
}
