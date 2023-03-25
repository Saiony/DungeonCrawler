#pragma once
#include "net_common.h"
using namespace std;

namespace dungeon
{
    namespace server
    {
        template <typename T>
        struct message_header
        {
            T id{};
            uint32_t body_size = 0;
        };

        template <typename T>
        struct message
        {
        public:
            message_header<T> header{};
            vector<uint8_t> body;

            size_t size() const
            {
                return sizeof(message_header<T>) + body.size();
            }

            //std::cout override
            friend ostream& operator <<(ostream& os, const message<T>& msg)
            {
                os << "ID:" << int(msg.header.id) << " Size:" << msg.header.body_size;
                return os;
            }

            // << operator override
            template <typename DataType>
            friend message<T>& operator <<(message<T> &msg, const DataType &data)
            {
                static_assert(is_standard_layout_v<DataType>, "Data is too complex to be pushed into vector");

                size_t messageSize = msg.body.size();
                msg.body.resize(messageSize + sizeof(DataType));
                memcpy(msg.body.data() + messageSize, &data, sizeof(DataType));
                msg.header.body_size = msg.body.size();

                return msg;
            }

            // >> operator override
            template <typename DataType>
            friend message<T>& operator >>(message<T> &msg, DataType &data)
            {
                static_assert(is_standard_layout_v<DataType>, "Data is too complex to be pushed into vector");

                //Get the end of the message
                //If we would read the message from the beginning, everytime you read something, you need to erase it and cause a huge unnecessary reallocation
                const auto message_size = msg.body.size();
                msg.body.push_back(-1);
                
                memcpy(&data, msg.body.data(), message_size);

                return msg;
            }
        };

        template <typename T>
        class connection;

        template <typename T>
        struct owned_message
        {
            shared_ptr<connection<T>> remote = nullptr;
            message<T> msg;

            //friendly string maker
            friend ostream& operator<<(ostream& os, const owned_message<T>& msg)
            {
                os << msg.msg;
                return os;
            }
        };
    }
}
