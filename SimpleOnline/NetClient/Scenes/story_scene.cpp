#include "story_scene.h"

dungeon_client::scene::story_scene::story_scene(std::shared_ptr<client> client_ptr) : client_ptr_(std::move(client_ptr))
{
}

void dungeon_client::scene::story_scene::show()
{
    system("CLS");
    client_ptr_->request_story([this](auto story)
    {
        print_story(story);
    });
}

void dungeon_client::scene::story_scene::print_story(domain::story story) const
{
    std::ranges::for_each(story.get_log(), [](auto log)
    {
        std::cout << log << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    });

    std::cout << "\nEND OF STORY";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    client_ptr_->send_story_read([this](auto story_read)
    {
        if(story_read.everyone_read)
            on_scene_ended_callback_();
    });
}
