#include "Player.h"

#include <iostream>
using namespace dungeon::server;
using namespace std;

void player::do_something()
{
    cout << "My id is " << id << endl;
}

player::player(const uint32_t player_id)
{
    id = player_id;
}