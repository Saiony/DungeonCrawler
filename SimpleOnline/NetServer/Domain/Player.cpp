#include "Player.h"
#include <iostream>
#include <utility>

#include "Utility/guid_generator.h"

using namespace std;
using namespace dungeon_server::domain;

void player::do_something() const
{
    cout << "My id is " << private_id << endl;
}

player::player(std::string client_id, const string& new_name, const uint16_t new_health, const uint16_t new_damage)
                : base_creature(new_name, new_health, new_damage), private_id(std::move(client_id))
{
    public_id = dungeon_common::utility::guid_generator::create_guid();
}
