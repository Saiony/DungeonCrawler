#pragma once
#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"
#include "net_connection.h"

using namespace asio::ip;

namespace dungeon_common
{
    template <typename T>
    class base_client
    {
    private:
        tsqueue<owned_message<T>> messages_in_;
    protected:
        asio::io_context io_context_; //handles data transfer
        thread thread_context_; //...but it needs a thread of its own to execute its work commands
        unique_ptr<connection<T>> con_;

    public:

        bool connect(const string& host, const uint16_t port)
        {
            try
            {
                //Resolve hostname/ip-address into tangible physical address
                tcp::resolver resolver(io_context_);
                tcp::resolver::results_type endpoints = resolver.resolve(host, to_string(port));

                con_ = make_unique<connection<T>>(owner::client, io_context_, tcp::socket(io_context_), messages_in_);
                con_->connect_to_server(endpoints);
                thread_context_ = thread([this]()
                {
                    io_context_.run();
                });
            }
            catch (exception& e)
            {
                cerr << "Client Exception: " << e.what() << "\n";
                return false;
            }

            return true;
        }

        void disconnect()
        {
            if (is_connected())
                con_->disconnect();

            //Make sure we're done with the asio context and the thread
            io_context_.stop();
            if (thread_context_.joinable())
                thread_context_.join();

            //Destroy the connection obj
            con_.release();
        }

        bool is_connected()
        {
            return con_ ? con_->is_connected() : false;
        }

        void send(const message<T>& msg)
        {
            if (is_connected())
                con_->send(msg);
        }

        //Retrieve queue of messages from server
        tsqueue<owned_message<T>>& incoming()
        {
            return messages_in_;
        }
    };
}
