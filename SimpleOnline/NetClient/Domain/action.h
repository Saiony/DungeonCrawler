#pragma once
#include "Models/action_use_model.h"

namespace dungeon_client::domain
{
    class action
    {
    public:
        dungeon_common::model::action_types id;
        std::string name{};
        
        action();
        action(const dungeon_common::model::action_types id, std::string name);
    };
}
