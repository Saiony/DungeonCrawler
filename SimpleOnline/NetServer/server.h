#pragma once
#include<dungeon_network.h>
#include "Domain/Player.h"
#include "Domain/Lobby/lobby_domain.h"
using namespace dungeon_common;

namespace dungeon_server
{

    class server final : public base_server<custom_msg_types>
    {
    private:
        const uint8_t max_players_ = 3;
        std::string spells_[5] = {"BurningHands", "CharmPerson", "CureWounds", "MageArmor", "Thunderwave"};
        std::vector<domain::player> players_;
        domain::lobby::lobby_domain lobby_;

            
        
    protected:
        bool can_client_connect(const std::shared_ptr<connection<custom_msg_types>>& connection) override;
        void on_client_connect(const std::shared_ptr<connection<custom_msg_types>>& client) override;              
        void on_client_disconnect(std::shared_ptr<connection<custom_msg_types>> client) override;
        void on_message(const std::shared_ptr<connection<custom_msg_types>> client, message<custom_msg_types>& msg) override;

    public:
        explicit server(const uint16_t n_port);
    };
}
