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

    enemy::wolf wolf("Wolf", 10, 15);
    const vector<enemy::base_enemy> enemies = { wolf };
    encounter::encounter encounter(enemies);
    
    while (true)
    {
        server.update(150, false);
    
        // if (GetKeyState('A') & 0x8000)
        // {
        //     message<custom_msg_types> msg;
        //     msg.header.id = custom_msg_types::server_message;
        //     msg << player;
        //     //server.message_client(server.players_[0].private_id, msg);b
        //     server.broadcast_message(msg);
        // }
        // if (GetKeyState('B') & 0x8000)
        // {
        //     message<custom_msg_types> msg;
        //     msg.header.id = custom_msg_types::server_message;
        //     msg << "Msg automatica";
        //     // server.message_client(server.players_[1].private_id, msg);
        //
        //     const vector<uint32_t> clients {10'000, 10'001};
        //     server.multicast_message(msg, clients);
        // }
    }
}
