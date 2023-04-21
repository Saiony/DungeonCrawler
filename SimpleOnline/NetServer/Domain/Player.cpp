#include "Player.h"
#include <iostream>

using namespace std;
using namespace dungeon_server::domain;

void player::do_something() const
{
    cout << "My id is " << private_id << endl;
}

player::player(const uint16_t id, string name, uint16_t health) : private_id(id), health(health), name(std::move(name))
{
}