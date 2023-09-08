#pragma once
#include "elemental_property_type.h"
#include<map>

namespace dungeon_server::utility
{
    class weakness_util
    {
    private:
        inline static const std::map<dungeon_common::enums::elemental_property_type, std::map<dungeon_common::enums::elemental_property_type, int>> targets_weakness =
        {
            {
                dungeon_common::enums::elemental_property_type::normal, std::map<dungeon_common::enums::elemental_property_type, int>
                {
                }
            },
            {
                dungeon_common::enums::elemental_property_type::fire, std::map<dungeon_common::enums::elemental_property_type, int>
                {
                    {dungeon_common::enums::elemental_property_type::fire, -100},
                    {dungeon_common::enums::elemental_property_type::ice, -50},
                }
            },
            {
                dungeon_common::enums::elemental_property_type::ice, std::map<dungeon_common::enums::elemental_property_type, int>
                {
                    {dungeon_common::enums::elemental_property_type::fire, 200},
                    {dungeon_common::enums::elemental_property_type::electric, 200},
                    {dungeon_common::enums::elemental_property_type::ice, -50},
                }
            },
            {
                dungeon_common::enums::elemental_property_type::earth, std::map<dungeon_common::enums::elemental_property_type, int>
                {
                    {dungeon_common::enums::elemental_property_type::earth, -50},
                    {dungeon_common::enums::elemental_property_type::fire, 200},
                }
            },
            {
                dungeon_common::enums::elemental_property_type::electric, std::map<dungeon_common::enums::elemental_property_type, int>
                {
                    {dungeon_common::enums::elemental_property_type::electric, -100},
                    {dungeon_common::enums::elemental_property_type::earth, 200},
                }
            },
            {
                dungeon_common::enums::elemental_property_type::holy, std::map<dungeon_common::enums::elemental_property_type, int>
                {
                    {dungeon_common::enums::elemental_property_type::holy, -100},
                    {dungeon_common::enums::elemental_property_type::death, 200},
                }
            },
            {
                dungeon_common::enums::elemental_property_type::death, std::map<dungeon_common::enums::elemental_property_type, int>
                {
                    {dungeon_common::enums::elemental_property_type::death, -100},
                    {dungeon_common::enums::elemental_property_type::holy, 200},
                }
            },
        };
        
    public:
        static int get_attack_multiplier(dungeon_common::enums::elemental_property_type attack_type, dungeon_common::enums::elemental_property_type target_type);
    };
}
