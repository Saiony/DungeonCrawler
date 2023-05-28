#pragma once
#include "BaseScene.h"
#include "../client.h"

namespace dungeon_client::scene
{
    class character_creation_scene : public base_scene
    {
    private:
        std::shared_ptr<client> client_ptr_ = nullptr;
        void on_character_created() const;
    public:
        explicit character_creation_scene(const std::shared_ptr<client>& client_ptr);

        void show() override;
        void create_character();
        void confirm_character_creation(const std::string& player_name);
    };
}
