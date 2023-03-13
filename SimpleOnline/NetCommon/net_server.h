#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"
#include "net_connection.h"

namespace dungeon
{
    namespace network
    {
        template <typename T>
        class server_interface
        {
        public:
            server_interface(uint16_t port) : asio_acceptor_(asio_context_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
            {
            }

            virtual ~server_interface()
            {
                stop();
            }

            bool start()
            {
                try
                {
                    wait_for_client_connection();
                    thread_context_ = std::thread([this]()
                    {
                        asio_context_.run();
                    });
                }
                catch (std::exception& e)
                {
                    std::cerr << "[SERVER] Exception: " << e.what() << "\n";
                    return false;
                }

                std::cout << "[SERVER] Started!\n";
                return true;
            }

            void stop()
            {
                asio_context_.stop();

                //This may take some time, so we start a thread
                if (thread_context_.joinable())
                    thread_context_.join();

                std::cout << "[SERVER] Stopped!\n";
            }

            void wait_for_client_connection()
            {
                asio_acceptor_.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket)
                {
                    if (!ec)
                    {
                        std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << "\n";
                        std::shared_ptr<connection<T>> new_con = std::make_shared<connection<T>>(
                            connection<T>::owner::server, asio_context_, std::move(socket), messages_in_);

                        if (OnClientConnect(new_con))
                        {
                            deq_connections_.push_back(std::move(new_con));
                            deq_connections_.back()->ConnectToClient(id_counter_++);
                            std::cout << "[" << deq_connections_.back()->GetID() << "] Connection Approved\n";
                        }
                        else
                        {
                            std::cout << "[-----] Connection Denied\n";
                        }
                    }
                    else
                    {
                        std::cout << "[SERVER] New Connection Error: " << ec.message() << "\n";
                    }

                    wait_for_client_connection();
                });
            }

            void message_client(std::shared_ptr<connection<T>> client, const message<T>& msg)
            {
                if (client && client->IsConnected())
                {
                    client->Send(msg);
                }
                else
                {
                    OnClientDisconnect(client);
                    client.reset();
                    deq_connections_.erase(std::remove(deq_connections_.begin(), deq_connections_.end(), client),
                                           deq_connections_.end());
                }
            }

            void message_all_clients(const message<T>& msg, std::shared_ptr<connection<T>> ignore_client = nullptr)
            {
                bool invalid_client_exists = false;

                for (auto& client : deq_connections_)
                {
                    if (client && client->IsConnected())
                    {
                        if (client != ignore_client)
                            client->Send(msg);
                    }
                    else
                    {
                        OnClientDisconnect(client);
                        client.reset();
                        invalid_client_exists = true;
                    }

                    if (invalid_client_exists)
                        deq_connections_.erase(std::remove(deq_connections_.begin(), deq_connections_.end(), client),deq_connections_.end());
                }
            }

            void update(const size_t max_messages = -1, const bool wait = false)
            {
                if (wait)
                    messages_in_.wait();

                size_t message_count = 0;
                while (message_count < max_messages && !messages_in_.empty())
                {
                    auto msg = messages_in_.pop_front();
                    OnMessage(msg.remote, msg.msg);

                    message_count++;
                }
            }

        protected:
            virtual bool on_client_connect(std::shared_ptr<connection<T>> client)
            {
                return false;
            }

            virtual auto OnClientDisconnect(std::shared_ptr<connection<T>> client) -> void
            {
            }

            virtual void on_message(std::shared_ptr<connection<T>> client, message<T>& msg)
            {
            }

        protected:
            tsqueue<owned_message<T>> messages_in_;
            std::deque<std::shared_ptr<connection<T>>> deq_connections_;
            asio::io_context asio_context_;
            std::thread thread_context_;
            asio::ip::tcp::acceptor asio_acceptor_;
            uint32_t id_counter_ = 10000;
        };
    }
}