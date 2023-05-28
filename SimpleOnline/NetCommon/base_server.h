#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"
#include "net_connection.h"
#include "Utility/guid_generator.h"

namespace dungeon_common
{
    template <typename T>
    class base_server
    {
    protected:
        tsqueue<owned_message<T>> messages_in_;
        std::deque<std::shared_ptr<connection<T>>> connections_;
        asio::io_context asio_context_;
        std::thread thread_context_;
        tcp::acceptor asio_acceptor_;
        uint32_t id_counter_ = 10000;

        virtual void on_client_connect(const std::shared_ptr<connection<custom_msg_types>>&)
        {
        }

        virtual void on_client_disconnect(std::shared_ptr<connection<T>>)
        {
        }

        virtual void on_message(std::shared_ptr<connection<T>> client, message<T>&)
        {
        }

        virtual bool can_client_connect(const std::shared_ptr<connection<custom_msg_types>>&)
        {
            return false;
        }

    public:
        base_server(const uint16_t port) : asio_acceptor_(asio_context_, tcp::endpoint(tcp::v4(), port))
        {
        }

        virtual ~base_server()
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
            asio_acceptor_.async_accept([this](const std::error_code error_code, tcp::socket socket)
            {
                if (error_code)
                    std::cout << "[SERVER] New Connection Error: " << error_code.message() << std::endl;
                else
                {
                    std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << std::endl;
                    std::shared_ptr<connection<T>> new_con = make_shared<connection<T>>(owner::server, asio_context_, std::move(socket), messages_in_);

                    auto con_id = utility::guid_generator::create_guid();
                    new_con->connect_to_client(con_id);
                    on_client_connect(new_con);
                    connections_.push_back(move(new_con));
                }

                wait_for_client_connection();
            });
        }

        void message_client(std::string client_id, const message<T>& msg)
        {
            auto client_it = find_if(begin(connections_), end(connections_),
                                     [client_id](std::shared_ptr<connection<T>> con)
                                     {
                                         return con->get_id() == client_id;
                                     });

            auto client = *client_it;
            if (client_it != end(connections_) && client->is_connected())
            {
                client->send(msg);
                return;
            }

            on_client_disconnect(client);
            client.reset();
            connections_.erase(remove(connections_.begin(), connections_.end(), client), connections_.end());
        }

        void multicast_message(const message<T>& msg, std::vector<uint32_t> client_ids)
        {
            for_each(begin(connections_), end(connections_), [client_ids, msg](std::shared_ptr<connection<T>> con)
            {
                if (any_of(std::begin(client_ids), std::end(client_ids), [con](uint32_t client_id)
                {
                    return con->private_id_ == client_id;
                }))
                    con->send(msg);
            });
        }

        void broadcast_message(const message<T>& msg)
        {
            for_each(begin(connections_), end(connections_), [=](std::shared_ptr<connection<T>> con)
            {
                con->send(msg);
            });
        }

        void update(const size_t max_messages = -1, const bool wait = false)
        {
            if (wait)
                messages_in_.wait();

            size_t message_count = 0;
            while (message_count < max_messages && !messages_in_.empty())
            {
                auto msg = messages_in_.pop_front();
                on_message(msg.remote, msg.msg);

                message_count++;
            }
        }
    };
}
