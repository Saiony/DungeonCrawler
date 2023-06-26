#pragma once
#include "Models/action_use_model.h"

namespace dungeon_client::domain
{
    class action
    {
    public:
        dungeon_common::model::action_types id;
        std::string name{};
        uint8_t targets_count{};
        
        action();
        action(const dungeon_common::model::action_types id, std::string name, const uint8_t targets_count);
        bool needs_target() const;
    };
}
