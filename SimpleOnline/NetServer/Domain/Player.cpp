#include "Player.h"
#include <iostream>
#include "NetServer/Utility/guid_generator.h"

using namespace std;
using namespace dungeon_server::domain;

void player::do_something() const
{
    cout << "My id is " << private_id << endl;
}

player::player(const uint16_t client_id, string name, const uint16_t health) : private_id(client_id), health(health), name(std::move(name))
{
    public_id = utility::guid_generator::create_guid();
}