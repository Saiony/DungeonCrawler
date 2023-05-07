#include "Models/player_model.h"
#include "server.h"
#include "Domain/Encounter.h"
#include "Domain/Enemies/Wolf.h"

using namespace dungeon_server;
using namespace model;
using namespace dungeon_server::domain;

int main()
{
    server server(60000);
    server.start();

    const enemy::wolf wolf("Wolf", 10, 15);
    const vector<enemy::base_enemy> enemies = { static_cast<enemy::base_enemy>(wolf) };
    encounter::encounter encounter(enemies);
    
    while (true)
        server.update(150, false);
}
