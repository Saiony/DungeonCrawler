#include "base_action.h"

dungeon_server::domain::action::base_action::~base_action() = default;

dungeon_server::domain::action::base_action::base_action(const dungeon_common::model::action_model model, std::shared_ptr<encounter::encounter>& encounter)
                                        : id(model.id), target_id(model.target_id, std::size(model.target_id)), encounter(encounter)
{
}
