#include "LobbyScene.h"
#include "LevelScene.h"
#include <iostream>

using namespace dungeon_client::scene;
using namespace std;

lobby_scene::lobby_scene(const shared_ptr<client>& client_ptr)
{
    client_ptr_ = client_ptr;
}

void lobby_scene::show()
{
    system("CLS");
    const auto client_ptr = client_ptr_;
    const auto ready = ready_;

    client_ptr_->set_player_ready(false, [&](const domain::lobby_domain& lobby)
    {
        print_lobby(lobby);
        wait_player_ready(client_ptr, ready);
    });
}

void lobby_scene::wait_player_ready(const shared_ptr<client>& client_ptr, bool ready)
{
    client_ptr->read_input([&](const string& input)
    {
        if (input == "ok")
            ready = !ready;
        else
        {
            wait_player_ready(client_ptr, ready);
            return;
        }

        client_ptr->set_player_ready(ready, [&](const domain::lobby_domain& lobby)
        {
            print_lobby(lobby);

            if (lobby.start_match)
            {
                start_match();
                return;
            }

            wait_player_ready(client_ptr, ready);
        });
    });
}

void lobby_scene::start_match() const
{
    level_scene level_scene(client_ptr_);
    level_scene.show();
}

void lobby_scene::print_lobby(domain::lobby_domain lobby) const
{
    system("CLS");
    cout << "Waiting for other players..." << endl;
    cout << "-----------------------------------------" << endl;
    for (auto& player_lobby : lobby.players_ready)
    {
        cout << player_lobby.get_name() << "                     " << player_lobby.get_ready_text() << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "Type [OK] to toggle the ready state" << endl;
}
