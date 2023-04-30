#include "LevelScene.h"

dungeon_client::scene::level_scene::level_scene(const std::shared_ptr<client>& client_ptr)
{
    client_ptr_ = client_ptr;
}

void dungeon_client::scene::level_scene::show()
{
    system("CLS");
    cout << "--- GAME SCENE ---" << endl << endl;
}
