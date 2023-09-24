#pragma once
#include <algorithm>
#include <string>

namespace dungeon_client::utility
{
    class string_utility
    {
    public:
        static std::string to_lower(std::string text)
        {
            std::ranges::transform(text, text.begin(), [](auto x) { return tolower(x); });
            return text;
        }

        static bool compare_string(const std::string& string1, const std::string& string2)
        {
            return to_lower(string1) == to_lower(string2);
        }
    };
}
