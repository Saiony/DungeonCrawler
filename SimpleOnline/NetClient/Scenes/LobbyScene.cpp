#include "LobbyScene.h"
#include "combat_scene.h"
#include <iostream>

#include "gameplay_scene.h"
#include "../Utility/custom_print.h"

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

    client_ptr_->set_player_ready(false, [&](const domain::lobby& lobby)
    {
        print_lobby(lobby);
        wait_player_ready(client_ptr, ready);
    });
}

void lobby_scene::wait_player_ready(const shared_ptr<client>& client_ptr, bool ready)
{
    cout << "Type [OK] to toggle the ready state" << endl;
    client_ptr->read_input([&](const string& input)
    {
        if (input != "ok")
        {
            wait_player_ready(client_ptr, ready);
            return;
        }

        ready = !ready;
        client_ptr->set_player_ready(ready, [&](const domain::lobby& lobby)
        {
            print_lobby(lobby);

            if (lobby.start_match)
            {
                start_match(lobby);
                return;
            }

            wait_player_ready(client_ptr, ready);
        });
    });
}

void lobby_scene::start_match(const domain::lobby& lobby) const
{
    for (int i = 3; i > 0; i--)
    {
        print_lobby(lobby);
        cout << "Game starting in...\t" << to_string(i) << endl;
        this_thread::sleep_for(1.5s);
    }
    
    gameplay_scene gameplay_scene(client_ptr_);
    gameplay_scene.show();
}

void lobby_scene::print_lobby(domain::lobby lobby) const
{
    system("CLS");
    cout << "Waiting for other players..." << endl << endl;
    utility::custom_print::print_aligned("Name", 20);
    utility::custom_print::print_aligned("Class", 20);
    utility::custom_print::print_aligned("Status", 20);
    std::cout << std::endl << "-------------------------------------------------" << std::endl;
    for (auto& player_lobby : lobby.players_ready)
    {
        utility::custom_print::print_aligned(player_lobby.get_name(), 20);
        utility::custom_print::print_aligned(player_lobby.get_class().name, 20);
        utility::custom_print::print_aligned(player_lobby.get_ready_text(), 20);
        std::cout << std::endl;
    }
    cout << "-------------------------------------------------" << endl;
}
