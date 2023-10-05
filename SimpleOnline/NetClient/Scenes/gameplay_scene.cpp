#include "gameplay_scene.h"

#include "bonfire_scene.h"
#include "combat_scene.h"
#include "game_over_loss_scene.h"
#include "game_over_win_scene.h"
#include "story_scene.h"

dungeon_client::scene::gameplay_scene::gameplay_scene(std::shared_ptr<client> client_ptr): client_ptr_(std::move(client_ptr))
{
}

void dungeon_client::scene::gameplay_scene::show()
{
    request_new_state();
}

void dungeon_client::scene::gameplay_scene::on_state_ended()
{
    request_new_state();
}

void dungeon_client::scene::gameplay_scene::request_new_state()
{
    client_ptr_->request_next_state([this](auto answer)
    {
        switch (answer.state)
        {
        case dungeon_common::enums::gameplay_state_type::story:
            {
                story_scene story_scene(client_ptr_);
                story_scene.subscribe_on_end([this] { on_state_ended(); });
                story_scene.show();
                return;
            }
        case dungeon_common::enums::gameplay_state_type::combat:
            {
                combat_scene combat_scene(client_ptr_);
                combat_scene.subscribe_on_end([this] { on_state_ended(); });
                combat_scene.show();
                return;
            }
        case dungeon_common::enums::gameplay_state_type::bonfire:
            {
                bonfire_scene bonfire_scene(client_ptr_);
                bonfire_scene.subscribe_on_end([this] { on_state_ended(); });
                bonfire_scene.show();
                return;
            }
        case dungeon_common::enums::gameplay_state_type::game_over_win:
            {
                game_over_win_scene game_over_win;
                game_over_win.show();
                return;
            }
        case dungeon_common::enums::gameplay_state_type::game_over_loss:
            {
                game_over_loss_scene game_over_loss;
                game_over_loss.show();
                return;
            }
        default:
            {
                throw std::exception("Invalid gameplay type");
            }
        }
    });
}
