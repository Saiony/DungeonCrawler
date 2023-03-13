#pragma once
#include "net_common.h"

namespace dungeon
{
    namespace network
    {
        template <typename T>
        class tsqueue
        {
        public:
            tsqueue() = default;
            tsqueue(const tsqueue<T>&) = delete;

            virtual ~tsqueue()
            {
                clear();
            }

        public:
            const T& front()
            {
                std::lock_guard<std::mutex> lock(muxQueue); //locks code while returning

                return deqQueue.front();
            }

            const T& back()
            {
                std::lock_guard<std::mutex> lock(muxQueue); //locks code while returning

                return deqQueue.back();
            }

            void push_back(const T& item)
            {
                std::lock_guard<std::mutex> lock(muxQueue); //locks code while returning
                deqQueue.emplace_back(std::move(item));
            }

            void push_front(const T& item)
            {
                std::lock_guard<std::mutex> lock(muxQueue); //locks code while returning
                deqQueue.emplace_front(std::move(item));
            }

            bool empty()
            {
                std::lock_guard<std::mutex> lock(muxQueue); //locks code while returning

                return deqQueue.empty();
            }

            size_t count()
            {
                std::lock_guard<std::mutex> lock(muxQueue); //locks code while returning

                return deqQueue.size();
            }

            void clear()
            {
                std::lock_guard<std::mutex> lock(muxQueue); //locks code while returning
                deqQueue.clear();
            }

            T pop_front()
            {
                std::lock_guard<std::mutex> lock(muxQueue); //locks code while returning
                auto t = std::move(deqQueue.front());
                deqQueue.pop_front();

                return t;
            }

            T pop_back()
            {
                std::lock_guard<std::mutex> lock(muxQueue); //locks code while returning
                auto t = std::move(deqQueue.back());
                deqQueue.pop_back();

                return t;
            }

            void wait()
            {
                while (empty())
                {
                    std::unique_lock<std::mutex> ul(muxBlocking);
                    cvBlocking.wait(ul);
                }
            }

        protected:
            std::mutex muxQueue;
            std::deque<T> deqQueue;
            std::condition_variable cvBlocking;
            std::mutex muxBlocking;
        };
    }
}