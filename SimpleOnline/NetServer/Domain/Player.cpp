#include "Player.h"

#include <iostream>
using namespace dungeon_common::domain;
using namespace std;

void player::do_something()
{
    cout << "My id is " << private_id << endl;
}

player::player(const uint16_t id, string name, uint16_t health) : private_id(id), health(health), name(std::move(name))
{
}