#include "action_model.h"
using namespace dungeon_common::model;

action_model::action_model(const action_types id, std::string new_target_id) : id(id)
{
    std::ranges::copy(new_target_id, target_id);
}

action_model::action_model() : id(action_types::unknown)
{    
}
