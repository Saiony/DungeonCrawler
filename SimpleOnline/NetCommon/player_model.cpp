#include "player_model.h"
#include <cstring>

player_model::player_model() = default;

player_model::player_model(const uint16_t id, char name[], const uint16_t health) : id_(id), health_(health)
{
    strcpy_s(name_, name);
}
