#pragma once
namespace dungeon_client::domain
{
    struct story_read
    {
        bool everyone_read{};    

        story_read();
        explicit story_read(bool everyone_read);
    };
}