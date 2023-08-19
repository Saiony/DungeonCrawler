#pragma once
#include "player_classes_model.h"

namespace dungeon_common::model
{
    class player_model
    {
    public:
        char id[39]{};
        char name[40]{};
        player_class_model player_class;
        uint32_t health{};
        
        player_model();
        player_model(const std::string& new_id, const std::string& new_name, const player_class_model& player_class, const uint32_t health);
    };
}
