#pragma once
#include "../client.h"

namespace dungeon_client::scene
{
    class character_creation_scene
    {
    private:
        shared_ptr<client> client_ptr_ = nullptr;
    public:
        explicit character_creation_scene(const shared_ptr<client>& client_ptr);

        void init();
        void confirm_character_creation(const string& player_name);
        void create_character();
    };
}
