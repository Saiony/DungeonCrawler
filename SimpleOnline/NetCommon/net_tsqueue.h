#pragma once
#include "net_common.h"

namespace dungeon_common
{
    template <typename T>
    class tsqueue
    {
    protected:
        mutex mux_queue_;
        deque<T> deq_queue_;
        condition_variable cv_blocking_;
        mutex mux_blocking_;

    public:
        tsqueue() = default;
        tsqueue(const tsqueue<T>&) = delete;

        virtual ~tsqueue()
        {
            clear();
        }

        const T& front()
        {
            lock_guard<mutex> lock(mux_queue_); //locks code while returning

            return deq_queue_.front();
        }

        const T& back()
        {
            lock_guard<mutex> lock(mux_queue_); //locks code while returning

            return deq_queue_.back();
        }

        void push_back(const T& item)
        {
            lock_guard<mutex> lock(mux_queue_); //locks code while returning
            deq_queue_.emplace_back(move(item));
        }

        void push_front(const T& item)
        {
            lock_guard<mutex> lock(mux_queue_); //locks code while returning
            deq_queue_.emplace_front(move(item));
        }

        bool empty()
        {
            lock_guard<mutex> lock(mux_queue_); //locks code while returning

            return deq_queue_.empty();
        }

        size_t count()
        {
            lock_guard<mutex> lock(mux_queue_); //locks code while returning

            return deq_queue_.size();
        }

        void clear()
        {
            lock_guard<mutex> lock(mux_queue_); //locks code while returning
            deq_queue_.clear();
        }

        T pop_front()
        {
            lock_guard<mutex> lock(mux_queue_); //locks code while returning
            auto t = move(deq_queue_.front());
            deq_queue_.pop_front();

            return t;
        }

        T pop_back()
        {
            lock_guard<mutex> lock(mux_queue_); //locks code while returning
            auto t = move(deq_queue_.back());
            deq_queue_.pop_back();

            return t;
        }

        void wait()
        {
            while (empty())
            {
                unique_lock<mutex> ul(mux_blocking_);
                cv_blocking_.wait(ul);
            }
        }
    };
}
