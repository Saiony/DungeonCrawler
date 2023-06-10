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
        std::string target_id;
        std::shared_ptr<encounter> encounter;

        explicit base_action(dungeon_common::model::action_model model, const std::shared_ptr<domain::encounter>& encounter);
        virtual void use()
        {
            std::cout << "base use " << std::endl;
        }
    };
}
