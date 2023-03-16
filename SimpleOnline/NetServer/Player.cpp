#include "Player.h"

#include <iostream>
using namespace dungeon::server;
using namespace std;

void player::do_something()
{
    cout << "My id is " << private_id << endl;
}

player::player(const uint32_t player_id)
{
    private_id = player_id;
}