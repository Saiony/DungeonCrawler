#pragma once
#include<dungeon_network.h>
#include "Domain/Encounter.h"
#include "Domain/Lobby/lobby_domain.h"
#include "Domain/Message/emitter_message.h"
#include "game_room/game_room.h"

namespace dungeon_server
{

    class server final : public dungeon_common::base_server<dungeon_common::custom_msg_types>
    {
    private:
        const uint8_t max_players_ = 3;
        std::vector<domain::player> players_;
        domain::lobby::lobby_domain lobby_;
        std::unique_ptr<game_room::game_room> game_room_ptr_;
        
    protected:
        bool can_client_connect(const std::shared_ptr<dungeon_common::connection<dungeon_common::custom_msg_types>>& connection) override;
        void on_client_connect(const std::shared_ptr<dungeon_common::connection<dungeon_common::custom_msg_types>>& client) override;              
        void on_client_disconnect(std::shared_ptr<dungeon_common::connection<dungeon_common::custom_msg_types>> client) override;
        void on_message(const std::shared_ptr<dungeon_common::connection<dungeon_common::custom_msg_types>> client, dungeon_common::message<dungeon_common::custom_msg_types>& msg) override;

    public:
        void update(const size_t max_messages = -1, const bool wait = false) override;//TODO: isso vira protected
        void on_game_room_message(const std::shared_ptr<domain::message::emitter_message>& emitter_msg);
        explicit server(const uint16_t n_port);
    };
}
