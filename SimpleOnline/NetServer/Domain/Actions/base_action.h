#pragma once
#include <iostream>

#include "Models/action_model.h"
#include "NetClient/Domain/encounter.h"
#include "NetServer/Domain/Encounter.h"

namespace domain::action
{
    class base_action
    {
    public:
        virtual ~base_action() = default;
        dungeon_common::model::action_types id;
        std::string target_id;
        std::shared_ptr<dungeon_server::domain::encounter::encounter> encounter;

        explicit base_action(dungeon_common::model::action_model model, std::shared_ptr<dungeon_server::domain::encounter::encounter>& encounter);
        virtual void use()
        {
            std::cout << "base use " << std::endl;
        }
    };
}
