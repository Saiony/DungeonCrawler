#pragma once

namespace dungeon_common::model
{
    struct story_read_model
    {
        bool everyone_read{};
        
        story_read_model();
        explicit story_read_model(bool everyone_read);
    };
}