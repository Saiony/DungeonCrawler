#include "player_model.h"
#include <cstring>
#include <string>

using namespace dungeon_common::model;

player_model::player_model() = default;

player_model::player_model(const uint16_t id, std::string name, const uint16_t health) : id_(id), health_(health)
{
    std::copy(begin(name), end(name), name_);
}
