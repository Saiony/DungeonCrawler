#pragma once
#include "net_common.h"

namespace dungeon_common
{
    enum class custom_msg_types
    {
        unknown = 0,
        server_connection_response,
        message_all,
        server_message,
        spell_consult,
        validate_name,
        get_player_classes,
        get_player_classes_response,
        create_player,
        player_ready,
        player_ready_response,
        get_gameplay_state,
        gameplay_state_response,
        match_start_request,
        encounter_update_response,
        player_action,
        game_room_broadcast,
        match_start_response,
        story_request,
        story_response,
        confirm_story_read,
        story_read_response,
        bonfire_story_teller_request,
        bonfire_story_teller_response,
        bonfire_story,
        bonfire_result_response,
    };
    
    template <typename T>
    struct message_header
    {
        T id{};
        uint32_t body_size = 0;
        
        message_header(custom_msg_types header_id) : id(header_id)
        {            
        }
    };

    template <typename T>
    struct message
    {
    public:
        message_header<T> header{};
        std::vector<uint8_t> body;

        message() : header(custom_msg_types::unknown)
        {
        }

        message(custom_msg_types msg_type) : header(msg_type)
        {            
        }

        size_t size() const
        {
            return sizeof(message_header<T>) + body.size();
        }

        //std::cout override
        friend std::ostream& operator <<(std::ostream& os, const message<T>& msg)
        {
            os << "ID:" << int(msg.header.public_id) << " Size:" << msg.header.body_size;
            return os;
        }

        // << operator override
        template <typename DataType>
        friend message<T>& operator <<(message<T>& msg, const DataType& data)
        {
            static_assert(std::is_standard_layout_v<DataType>, "Data is too complex to be pushed into vector");

            size_t message_size = msg.body.size();
            msg.body.resize(message_size + sizeof(DataType));
            memcpy(msg.body.data() + message_size, &data, sizeof(DataType));
            msg.header.body_size = msg.body.size();

            return msg;
        }

        // >> operator override
        template <typename DataType>
        friend message<T>& operator >>(message<T>& msg, DataType& data)
        {
            static_assert(std::is_trivially_copyable_v<DataType>, "Data is too complex to be pushed into vector");

            //Get the end of the message
            //If we would read the message from the beginning, everytime you read something, you need to erase it and cause a huge unnecessary reallocation
            const auto message_size = msg.body.size();
            msg.body.push_back(-1);

            memcpy(&data, msg.body.data(), message_size);

            return msg;
        }

        std::string read_body()
        {
            std::string s(begin(body), end(body));
            return s;
        }
    };

    template <typename T>
    class connection;

    template <typename T>
    struct owned_message
    {
        std::shared_ptr<connection<T>> remote = nullptr;
        message<T> msg;

        //friendly string maker
        friend std::ostream& operator<<(std::ostream& os, const owned_message<T>& msg)
        {
            os << msg.msg;
            return os;
        }
    };
}
