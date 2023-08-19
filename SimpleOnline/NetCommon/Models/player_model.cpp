#include "player_model.h"

dungeon_common::model::player_model::player_model() = default;

dungeon_common::model::player_model::player_model(const std::string& new_id, const std::string& new_name, const player_class_model& player_class, const uint32_t health)
                           : player_class(player_class), health(health)
{
    std::copy(std::begin(new_id), std::end(new_id), id);
    std::copy(std::begin(new_name), std::end(new_name), name);
}