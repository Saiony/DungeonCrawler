#include "lobby_model.h"

#include <algorithm>
using namespace dungeon_common::model;
using namespace std;

player_lobby_model::player_lobby_model(const char* player_name, const bool ready) : ready(ready)
{
    strcpy_s(begin(name), size(name), player_name);
}

player_lobby_model::player_lobby_model() : name("-")
{    
}

void player_lobby_model::set_ready(const bool ready_state)
{
    ready = ready_state;
}

lobby_model::lobby_model(): players_lobby_status()
{
}
