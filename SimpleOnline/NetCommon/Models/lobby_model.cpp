#include "lobby_model.h"

#include <algorithm>
using namespace dungeon_common::model;
using namespace std;

player_lobby_model::player_lobby_model(const char* player_name, player_class_model player_class, const bool ready) : player_class(player_class), ready(ready)
{
    strcpy_s(begin(name), size(name), player_name);
}

player_lobby_model::player_lobby_model() : name("-"), player_class(enums::player_class_type::unknown, "-"), ready(false)
{    
}

void player_lobby_model::set_ready(const bool ready_state)
{
    ready = ready_state;
}

lobby_model::lobby_model(): players_lobby_status()
{
}
