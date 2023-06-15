#pragma once
#include <iostream>
#include "Models/action_model.h"
#include "NetServer/Domain/Encounter.h"

namespace dungeon_server::domain::action
{
    class base_action
    {
    public:
        virtual ~base_action();
        dungeon_common::model::action_types id;

        explicit base_action(const dungeon_common::model::action_types& action_type);
        
        virtual void use(const std::shared_ptr<encounter>& encounter_ptr)
        {
            std::cout << "base use " << std::endl;
        }
    };
}
