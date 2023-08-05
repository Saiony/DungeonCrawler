#pragma once
#include "Models/action_use_model.h"
#include "NetServer/Domain/Actions/base_action.h"

namespace dungeon_server::domain::action
{
     class action_factory
     {
     public:
          static std::shared_ptr<base_action> create_action(dungeon_common::model::action_use_model action_model);
          static std::shared_ptr<base_action> create_action(dungeon_common::model::action_types action_type, const std::string& owner_id,
                                                            const std::string& target_id = {});
     };
}