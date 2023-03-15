#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

namespace dungeon
{
    namespace server
    {
        template <typename T>
        class connection : public std::enable_shared_from_this<connection<T>>
        {
        public:
            enum class owner
            {
                server,
                client
            };

        public:
            connection(owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>>& qIn)
                        : asio_context_(asioContext), socket_(std::move(socket)), messages_in_(qIn)
            {
                owner_type_ = parent;
            }

            virtual ~connection() = default;

            // This ID is used system wide - its how clients will understand other clients
            // exist across the whole system.
            uint32_t get_id() const
            {
                return id_;
            }

        public:
            void connect_to_client(uint32_t uid = 0)
            {
                std::cout << "\nConnectToClient\n";
                if (owner_type_ == owner::server)
                {
                    if (socket_.is_open())
                    {
                        id_ = uid;
                        read_header();
                    }
                }
            }

            void connect_to_server(const asio::ip::tcp::resolver::results_type& endpoints)
            {
                std::cout << "\nConnectToServer\n";
                if (owner_type_ != owner::client)
                    return;

                asio::async_connect(socket_, endpoints,
                                    [this](std::error_code ec, asio::ip::tcp::endpoint const endpoint)
                                    {
                                        if (!ec)
                                        {
                                            read_header();
                                        }
                                    });
            }


            void disconnect()
            {
                if (is_connected())
                    asio::post(asio_context_, [this]() { socket_.close(); });
            }

            bool is_connected() const
            {
                return socket_.is_open();
            }

        public:
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
                                 [this](std::error_code errorCode, std::size_t length)
                                 {
                                     if (!errorCode)
                                     {
                                         if (temporary_message_in_.header.body_size > 0)
                                         {
                                             temporary_message_in_.body.resize(temporary_message_in_.header.body_size);
                                             read_body();
                                         }
                                         else
                                             add_to_incoming_message_queue();
                                     }
                                     else
                                     {
                                         std::cout << "\n[" << id_ << "] Read Header Fail.\n";
                                         socket_.close();
                                     }
                                 });
            }

        private:
            void write_header()
            {
                asio::async_write(socket_, asio::buffer(&messages_out_.front().header, sizeof(message_header<T>)),
                                  [this](std::error_code errorCode, std::size_t length)
                                  {
                                      if (!errorCode)
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
                                          socket_.close();
                                      }
                                  });
            }

            void write_body()
            {
                asio::async_write(
                    socket_, asio::buffer(messages_out_.front().body.data(), messages_out_.front().header.body_size),
                    [this](std::error_code errorCode, std::size_t length)
                    {
                        if (!errorCode)
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
                            socket_.close();
                        }
                    });
            }

            void read_body()
            {
                asio::async_read(socket_, asio::buffer(temporary_message_in_.body.data(), temporary_message_in_.body.size()),
                                 [this](std::error_code errorCode, std::size_t length)
                                 {
                                     if (!errorCode)
                                         add_to_incoming_message_queue();
                                     else
                                     {
                                         std::cout << "[" << id_ << "] Read Body Fail.\n";
                                         socket_.close();
                                     }
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

        protected:
            asio::ip::tcp::socket socket_;
            asio::io_context& asio_context_;
            tsqueue<message<T>> messages_out_;
            tsqueue<owned_message<T>>& messages_in_;
            message<T> temporary_message_in_;
            owner owner_type_ = owner::server;
            uint32_t id_ = 0;
        };
    }
}
