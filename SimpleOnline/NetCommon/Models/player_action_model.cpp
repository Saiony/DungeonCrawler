#include "player_action_model.h"

player_action_model::player_action_model() = default;

player_action_model::player_action_model(const dungeon_common::model::action_types id, std::string new_name, const uint8_t targets_number)
                                        : id(id), targets_count(targets_number)
{
    std::ranges::copy(new_name, std::begin(name));
}
