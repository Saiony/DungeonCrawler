#pragma once
#include "BaseScene.h"
#include "../client.h"

namespace dungeon_client::scene
{
    class character_creation_scene : public base_scene
    {
    private:
        std::shared_ptr<client> client_ptr_ = nullptr;
        std::string player_name_;
        dungeon_common::enums::player_class_type player_class_;
        
        void on_character_created() const;
        void create_name();
        void create_class();
    public:
        explicit character_creation_scene(const std::shared_ptr<client>& client_ptr);

        void show() override;
        void create_character();
        void confirm_character_creation();
    };
}
