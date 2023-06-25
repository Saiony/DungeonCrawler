#include "action_use_model.h"

#include "../net_connection.h"
using namespace dungeon_common::model;

action_use_model::action_use_model(const action_types id, std::string new_owner_id, std::string new_target_id) : id(id)
{
    std::copy(std::begin(new_target_id), std::end(new_target_id), target_id);
    std::copy(std::begin(new_owner_id), std::end(new_owner_id), owner_id);
}

action_use_model::action_use_model() : id(action_types::unknown)
{    
}
