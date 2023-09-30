#include "bonfire_scene.h"

dungeon_client::scene::bonfire_scene::bonfire_scene(std::shared_ptr<client> client_ptr): client_ptr_(std::move(client_ptr))
{
}

void dungeon_client::scene::bonfire_scene::show()
{
    system("CLS");
    std::cout << "===========" << std::endl;
    std::cout << "  BONFIRE  " << std::endl;
    std::cout << "===========" << std::endl;

    client_ptr_->request_bonfire_story_teller([this](auto story_teller)
    {
        if (story_teller.public_id == client_ptr_->get_player().public_id)
        {
            std::cout << "You are the story teller..." << std::endl;
        }
        else            
            std::cout << "Story teller: " + story_teller.name;
        
        std::this_thread::sleep_for(std::chrono::seconds(5));
    });
}
