#include "base_action.h"

domain::action::base_action::base_action(const dungeon_common::model::action_model model, std::shared_ptr<dungeon_server::domain::encounter::encounter>& encounter)
                                        : id(model.id), target_id(model.target_id), encounter(encounter)
{
}
