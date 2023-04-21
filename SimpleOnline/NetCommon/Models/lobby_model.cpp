#include "lobby_model.h"

#include <algorithm>
using namespace dungeon_common::model;
using namespace std;

player_lobby_model::player_lobby_model(const char* name, const bool ready) : ready_(ready)
{
    strcpy_s(begin(name_), size(name_), name);
}

player_lobby_model::player_lobby_model() : name_("-")
{    
}

void player_lobby_model::set_ready(const bool ready)
{
    ready_ = ready;
}

lobby_model::lobby_model(): players_lobby_status()
{
}
