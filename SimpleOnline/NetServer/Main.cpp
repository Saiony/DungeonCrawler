#include "net_message.h"
#include "Models/player_model.h"
#include "server.h"

int main()
{
    server server(60000);
    server.start();

    //Debug Player Model
    char name[40]("Jefferson Caminhoes");
    const player_model player(10000, name, 27);
    
    while (true)
    {
        server.update(150, false);
    
        if (GetKeyState('A') & 0x8000)
        {
            message<custom_msg_types> msg;
            msg.header.id = custom_msg_types::server_message;
            msg << player;
            //server.message_client(server.players_[0].private_id, msg);b
            server.broadcast_message(msg);
        }
        if (GetKeyState('B') & 0x8000)
        {
            message<custom_msg_types> msg;
            msg.header.id = custom_msg_types::server_message;
            msg << "Msg automatica";
            // server.message_client(server.players_[1].private_id, msg);
    
            const vector<uint32_t> clients {10'000, 10'001};
            server.multicast_message(msg, clients);
        }
    }
}
