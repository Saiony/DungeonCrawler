#include "server.h"

using namespace dungeon_server;

int main()
{
    server server(14414);
    server.start();

    while (true)
        server.update(150, false);
}
