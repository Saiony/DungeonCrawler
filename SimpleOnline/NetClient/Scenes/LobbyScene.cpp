#include "LobbyScene.h"
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
    auto client_ptr = client_ptr_;
    auto ready = ready_;
    
    client_ptr_->set_player_ready(false, [this, client_ptr, ready](const domain::lobby_domain& lobby)
    {
        print_lobby(lobby);
    });

    //locks thread and waits for condition var
    std::unique_lock<std::mutex> lock{client_ptr_->mutex};
    client_ptr_->condition_var.wait(lock);        
    const auto response = client_ptr_->set_player_ready_response;
    lock.unlock();
    
    wait_player_ready(client_ptr, ready);
}


void lobby_scene::wait_player_ready(const shared_ptr<client>& client_ptr, bool ready)
{
    string input;    
    getline(cin, input);
    
    if (input == "ok")
        ready = !ready;
    else
    {
        wait_player_ready(client_ptr, ready);
        return;
    }

    client_ptr->set_player_ready(ready, [this, client_ptr, ready](const domain::lobby_domain& lobby)
    {
        print_lobby(lobby);
    });
    wait_player_ready(client_ptr, ready);
}

void lobby_scene::print_lobby(domain::lobby_domain lobby) const
{    
    system("CLS");
    cout << "Waiting for other players..." << endl;
    cout << "-----------------------------------------" << endl;
    for (auto& player_lobby : lobby.players_ready_)
    {
        cout << player_lobby.get_name() << "                     " << player_lobby.get_ready() << endl;
    }
    cout << "-----------------------------------------" << endl;    
    cout << "Type [OK] to toggle the ready state" << endl;
}




