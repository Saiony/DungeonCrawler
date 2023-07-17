#include "game_over_win_scene.h"

#include <iostream>

void dungeon_client::scene::game_over_win_scene::show()
{
    system("CLS");
    std::cout << "YOU WON!!" << std::endl << std::endl;
    std::cout << "Thanks for playing the beta" << std::endl;
    std::cout << "Please, feel free to give us feedbacks on your experience" << std::endl;
}
