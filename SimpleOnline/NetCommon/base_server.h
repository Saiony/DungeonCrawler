#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"
#include "net_connection.h"
#include <algorithm>

namespace dungeon_common
{
    template <typename T>
    class base_server
    {
    protected:
        tsqueue<owned_message<T>> messages_in_;
        deque<shared_ptr<connection<T>>> connections_;
        asio::io_context asio_context_;
        thread thread_context_;
        tcp::acceptor asio_acceptor_;
        uint32_t id_counter_ = 10000;

        virtual void on_client_connect(shared_ptr<connection<T>>)
        {
        }

        virtual void on_client_disconnect(shared_ptr<connection<T>>)
        {
        }

        virtual void on_message(shared_ptr<connection<T>> client, message<T>&)
        {
        }

        virtual bool can_client_connect(shared_ptr<connection<T>>)
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
                thread_context_ = thread([this]()
                {
                    asio_context_.run();
                });
            }
            catch (exception& e)
            {
                cerr << "[SERVER] Exception: " << e.what() << "\n";
                return false;
            }

            cout << "[SERVER] Started!\n";
            return true;
        }

        void stop()
        {
            asio_context_.stop();

            //This may take some time, so we start a thread
            if (thread_context_.joinable())
                thread_context_.join();

            cout << "[SERVER] Stopped!\n";
        }

        void wait_for_client_connection()
        {
            asio_acceptor_.async_accept([this](const error_code error_code, tcp::socket socket)
            {
                if (error_code)
                    cout << "[SERVER] New Connection Error: " << error_code.message() << endl;
                else
                {
                    cout << "[SERVER] New Connection: " << socket.remote_endpoint() << endl;
                    shared_ptr<connection<T>> new_con = make_shared<connection<T>>(
                        owner::server, asio_context_, move(socket), messages_in_);

                    if (can_client_connect(new_con))
                    {
                        new_con->connect_to_client(id_counter_++);
                        on_client_connect(new_con);
                        connections_.push_back(move(new_con));
                        cout << "[" << connections_.back()->get_id() << "] Connection Approved\n";
                    }
                    else
                    {
                        cout << "[-----] Connection Denied\n";
                    }
                }

                wait_for_client_connection();
            });
        }

        void message_client(uint32_t client_id, const message<T>& msg)
        {
            auto client_it = find_if(begin(connections_), end(connections_),
                                     [client_id](shared_ptr<connection<T>> con)
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

        void multicast_message(const message<T>& msg, vector<uint32_t> client_ids)
        {
            for_each(begin(connections_), end(connections_), [client_ids, msg](shared_ptr<connection<T>> con)
            {
                if (any_of(begin(client_ids), end(client_ids), [con](uint32_t client_id)
                {
                    return con->private_id_ == client_id;
                }))
                    con->send(msg);
            });
        }

        void broadcast_message(const message<T>& msg)
        {
            for_each(begin(connections_), end(connections_), [=](shared_ptr<connection<T>> con)
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
