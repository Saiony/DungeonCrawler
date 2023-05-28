#pragma once
#include "net_common.h"

namespace dungeon_common
{
    template <typename T>
    class tsqueue
    {
    protected:
        std::mutex mux_queue_;
        std::deque<T> deq_queue_;
        std::condition_variable cv_blocking_;
        std::mutex mux_blocking_;

    public:
        tsqueue() = default;
        tsqueue(const tsqueue<T>&) = delete;

        virtual ~tsqueue()
        {
            clear();
        }

        const T& front()
        {
            std::lock_guard<std::mutex> lock(mux_queue_); //locks code while returning

            return deq_queue_.front();
        }

        const T& back()
        {
            std::lock_guard<std::mutex> lock(mux_queue_); //locks code while returning

            return deq_queue_.back();
        }

        void push_back(const T& item)
        {
            std::lock_guard<std::mutex> lock(mux_queue_); //locks code while returning
            deq_queue_.emplace_back(std::move(item));
        }

        void push_front(const T& item)
        {
            std::lock_guard<std::mutex> lock(mux_queue_); //locks code while returning
            deq_queue_.emplace_front(move(item));
        }

        bool empty()
        {
            std::lock_guard<std::mutex> lock(mux_queue_); //locks code while returning

            return deq_queue_.empty();
        }

        size_t count()
        {
            std::lock_guard<std::mutex> lock(mux_queue_); //locks code while returning

            return deq_queue_.size();
        }

        void clear()
        {
            std::lock_guard<std::mutex> lock(mux_queue_); //locks code while returning
            deq_queue_.clear();
        }

        T pop_front()
        {
            std::lock_guard<std::mutex> lock(mux_queue_); //locks code while returning
            auto t = std::move(deq_queue_.front());
            deq_queue_.pop_front();

            return t;
        }

        T pop_back()
        {
            std::lock_guard<std::mutex> lock(mux_queue_); //locks code while returning
            auto t = std::move(deq_queue_.back());
            deq_queue_.pop_back();

            return t;
        }

        void wait()
        {
            while (empty())
            {
                std::unique_lock<std::mutex> ul(mux_blocking_);
                cv_blocking_.wait(ul);
            }
        }
    };
}
