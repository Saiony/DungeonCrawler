#include "Models/player_model.h"
#include "server.h"
#include "Domain/Encounter.h"
#include "Domain/Enemies/Wolf.h"
#include "Models/encounter_model.h"

using namespace dungeon_server;
using namespace model;
using namespace dungeon_server::domain;

int main()
{
    server server(60000);
    server.start();
    
    while (true)
        server.update(150, false);
}
