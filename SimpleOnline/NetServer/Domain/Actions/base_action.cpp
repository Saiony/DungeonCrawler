#include "base_action.h"
#include <utility>

using namespace dungeon_server::domain;

action::base_action::~base_action() = default;

action::base_action::base_action(const dungeon_common::model::action_types& action_type, std::string new_action_owner_id)
                                                        : id(action_type), action_owner_id(std::move(new_action_owner_id))
{
}

std::shared_ptr<base_creature> action::base_action::get_creature(const std::shared_ptr<encounter>& encounter_ptr, const std::string& creature_id)
{    
    auto action_owner = *std::ranges::find_if(encounter_ptr->creatures, [this, &creature_id](auto enemy)
    {
       return enemy->public_id == creature_id;
    });

    return action_owner;
}
