#pragma once
#include <string>
#include "combaseapi.h"
#include "objbase.h"

namespace dungeon_server::utility
{
    class guid_generator
    {
    public:
        static std::string create_guid()
        {
            GUID guid;
            CoCreateGuid(&guid);

            wchar_t guid_char[39];
            StringFromGUID2(guid, guid_char, 39);

            std::wstring wstr(guid_char);
            std::string guid_string(wstr.begin(), wstr.end());

            return guid_string;
        }
    };
}
