#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

using namespace asio::ip;

namespace dungeon_common
{
    enum class owner
    {
        server,
        client
    };

    template <typename T>
    class connection : public std::enable_shared_from_this<connection<T>>
    {
    private:
        std::function<void(std::shared_ptr<connection>)> on_disconnect_listener_;
    protected:
        tcp::socket socket_;
        asio::io_context& asio_context_;
        tsqueue<message<T>> messages_out_;
        tsqueue<owned_message<T>>& messages_in_;
        message<T> temporary_message_in_;
        owner owner_type_ = owner::server;
        char id_[39]{};
    public:

        connection(owner parent, asio::io_context& asio_context, tcp::socket socket, tsqueue<owned_message<T>>& q_in)
            : socket_(std::move(socket)), asio_context_(asio_context), messages_in_(q_in)
        {
            owner_type_ = parent;
        }

        virtual ~connection() = default;

        // This ID is used system wide - its how clients will understand other clients
        // exist across the whole system.
        std::string get_id() const
        {
            return id_;
        }

        void connect_to_client(std::string uid)
        {
            if (owner_type_ == owner::server)
            {
                if (socket_.is_open())
                {
                    strcpy_s(id_, uid.c_str());
                    read_header();
                }
            }
        }

        void connect_to_server(const tcp::resolver::results_type& endpoints)
        {
            if (owner_type_ != owner::client)
                return;

            asio::async_connect(socket_, endpoints,
                [this](std::error_code error_code, tcp::endpoint const& endpoint)
                {
                    if (error_code)
                        return;
                    
                    read_header();
                });
        }


        void disconnect()
        {
            if (is_connected())
                asio::post(asio_context_, [this]() { on_client_disconnect(); });
        }

        bool is_connected() const
        {
            return socket_.is_open();
        }

        void send(const message<T>& msg)
        {
            asio::post(asio_context_,
               [this, msg]()
               {
                   const bool writing_messages = !messages_out_.empty();
                   messages_out_.push_back(msg);
                   if (!writing_messages)
                   {
                       write_header();
                   }
               });
        }

        void read_header()
        {
            asio::async_read(socket_, asio::buffer(&temporary_message_in_.header, sizeof(message_header<T>)),
                 [this](const std::error_code error_code, size_t length)
                 {
                     if (error_code)
                     {
                         std::cout << "\n[" << id_ << "] Connection Lost\n";

                         on_client_disconnect();
                         return;
                     }
                     
                     if (temporary_message_in_.header.body_size > 0)
                     {
                         temporary_message_in_.body.resize(temporary_message_in_.header.body_size);
                         read_body();
                     }
                     else
                         add_to_incoming_message_queue();
                 });
        }

        void subscribe_on_disconnect(const std::function<void(std::shared_ptr<connection>)>& callback)
        {
            on_disconnect_listener_ = callback;
        }

    private:
        void on_client_disconnect()
        {
            socket_.close();
            on_disconnect_listener_(this->shared_from_this());
        }
        
        void write_header()
        {
            asio::async_write(socket_, asio::buffer(&messages_out_.front().header, sizeof(message_header<T>)),
                  [this](const std::error_code error_code, size_t length)
                  {
                      if (!error_code)
                      {
                          if (messages_out_.front().body.size() > 0)
                              write_body();
                          else
                          {
                              messages_out_.pop_front();

                              if (!messages_out_.empty())
                              {
                                  write_header();
                              }
                          }
                      }
                      else
                      {
                          std::cout << "[" << id_ << "] Write Header Fail.\n";
                          on_client_disconnect();
                      }
                  });
        }

        void write_body()
        {
            asio::async_write(
                socket_, asio::buffer(messages_out_.front().body.data(), messages_out_.front().header.body_size),
                [this](const std::error_code error_code, size_t length)
                {
                    if (!error_code)
                    {
                        messages_out_.pop_front();

                        if (!messages_out_.empty())
                        {
                            write_header();
                        }
                    }
                    else
                    {
                        std::cout << "[" << id_ << "] Write Body Fail.\n";
                        on_client_disconnect();
                    }
                });
        }

        void read_body()
        {
            asio::async_read(
                socket_, asio::buffer(temporary_message_in_.body.data(), temporary_message_in_.body.size()),
                [this](const std::error_code error_code, size_t length)
                {
                    if (error_code)
                    {
                        std::cout << "[" << id_ << "] Error: " + error_code.message() + "\n";
                        on_client_disconnect();
                        return;
                    }
                    
                    add_to_incoming_message_queue();
                });
        }

        void add_to_incoming_message_queue()
        {
            if (owner_type_ == owner::server)
                messages_in_.push_back({this->shared_from_this(), temporary_message_in_});
            else
                messages_in_.push_back({nullptr, temporary_message_in_});

            read_header();
        }
    };
}
