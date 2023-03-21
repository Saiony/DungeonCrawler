#include "PlayerModel.h"
using namespace dungeon::model;


player_model::player_model() = default;

player_model::player_model(const uint16_t id, char name_data[], const uint16_t health) : id(id), health(health)
{    
    strcpy_s(name, name_data);
}
