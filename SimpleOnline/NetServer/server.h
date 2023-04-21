#pragma once
#include<dungeon_network.h>
#include "Domain/Player.h"
#include "Domain/Lobby/player_lobby_domain.h"
#include "Models/lobby_model.h"

using namespace dungeon_common;

namespace dungeon_server
{

    class server final : public base_server<custom_msg_types>
    {
    private:
        string spells_[5] = {"BurningHands", "CharmPerson", "CureWounds", "MageArmor", "Thunderwave"};
        vector<domain::player> players_;
        vector<domain::lobby::player_lobby_domain> players_ready_;

    public:
        explicit server(const uint16_t n_port);


    protected:
        bool can_client_connect(shared_ptr<connection<custom_msg_types>> client) override;

        void on_client_connect(shared_ptr<connection<custom_msg_types>> client) override;

        void on_client_disconnect(shared_ptr<connection<custom_msg_types>> client) override;

        void on_message(const shared_ptr<connection<custom_msg_types>> client, message<custom_msg_types>& msg) override;
    };
}
