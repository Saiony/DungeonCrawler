#pragma once
#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"
#include "net_connection.h"

namespace dungeon
{
    namespace network
    {
        template <typename T>
        class client_interface
        {
        public:
            client_interface() = default;

            virtual ~client_interface()
            {
                disconnect();
            }

        public:
            bool connect(const std::string& host, const uint16_t port)
            {
                try
                {
                    //Resolve hostname/ip-address into tangible physical address
                    asio::ip::tcp::resolver resolver(ioContext);
                    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

                    con = std::make_unique<connection<T>>(connection<T>::owner::client, ioContext,
                                                          asio::ip::tcp::socket(ioContext), messagesIn);
                    con->connect_to_server(endpoints);
                    threadContext = std::thread([this]() { ioContext.run(); });
                }
                catch (std::exception& e)
                {
                    std::cerr << "Client Exception: " << e.what() << "\n";
                    return false;
                }

                return true;
            }

            void disconnect()
            {
                if (is_connected())
                    con->disconnect();

                //Make sure we're done with the asio context and the thread
                ioContext.stop();
                if (threadContext.joinable())
                    threadContext.join();

                //Destroy the connection obj
                con.release();
            }

            bool is_connected()
            {
                if (con)
                    return con->is_connected();
                else
                    return false;
            }

        public:
            void send(const message<T>& msg)
            {
                if (is_connected())
                    con->send(msg);
            }

            //Retrieve queue of messages from server
            tsqueue<owned_message<T>>& incoming()
            {
                return messagesIn;
            }

        protected:
            asio::io_context ioContext; //handles data transfer
            std::thread threadContext; //...but it needs a thread of its own to execute its work commands
            std::unique_ptr<connection<T>> con;

        private:
            tsqueue<owned_message<T>> messagesIn;
        };
    }
}
