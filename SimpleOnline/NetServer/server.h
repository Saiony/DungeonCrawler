#pragma once
#include<iostream>
#include<dungeon_network.h>
#include "Player.h"

using namespace dungeon::server;

enum class custom_msg_types : uint32_t
{
    server_accept,
    server_deny,
    spell_consult,
    message_all,
    server_message,
};

class server final : public base_server<custom_msg_types>
{
private:
    string spells_[5] = {"BurningHands", "CharmPerson", "CureWounds", "MageArmor", "Thunderwave"};
    vector<player> players_;

public:
    server(const uint16_t n_port);


protected:
    bool can_client_connect(shared_ptr<connection<custom_msg_types>> client) override;

    void on_client_connect(shared_ptr<connection<custom_msg_types>> client) override;

    void on_client_disconnect(shared_ptr<connection<custom_msg_types>> client) override;

    void on_message(const shared_ptr<connection<custom_msg_types>> client, message<custom_msg_types>& msg) override;
};

