#include "action_model.h"

action_model::action_model(const action_types id, const int target_id) : id(id), target_id(target_id)
{
}

action_model::action_model() : id(action_types::unknown), target_id(-1)
{
    
}
