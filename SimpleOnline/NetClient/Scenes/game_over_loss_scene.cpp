#include "game_over_loss_scene.h"

#include <iostream>

void dungeon_client::scene::game_over_loss_scene::show()
{
    system("CLS");
    std::cout << "GAME OVER" << std::endl << std::endl;
    std::cout << "Please close the application and restart the server to play again." << std::endl;
}
