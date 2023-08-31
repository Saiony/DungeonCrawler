#include "server.h"

using namespace dungeon_server;

int main()
{
    server server(14414);
    server.start();

    while (true)
    {
        if (server.running)
            server.update(150, false);
    }
}
