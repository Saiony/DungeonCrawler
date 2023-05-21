#include "player_model.h"
#include <cstring>
#include <string>

using namespace dungeon_common::model;

player_model::player_model() = default;

player_model::player_model(std::string new_id, std::string new_name, const uint32_t health) : health(health)
{
    std::copy(begin(new_id), end(new_id), id);
    std::copy(begin(new_name), end(new_name), name);
}
