//
// Created by 秋鱼 on 2022/6/20.
//

#include "thread_pool.hpp"

#include <utility>

namespace San {

ThreadPool::ThreadPool()
{
    for (auto i = 0; i < num_of_thread_; ++i) {
        threads_.emplace_back(
            [this]
            {
                while (true) {
                    Task task;
                    {
                        std::unique_lock lock{this->queue_mutex_};
                        this->condition_.wait(lock,
                                              [this]
                                              {
                                                  return this->stop_ ||
                                                      (!this->tasks_.empty() && (active_threads_num_ < num_of_thread_));
                                              });
                        if (this->stop_) {
                            return;
                        }

                        active_threads_num_ += 1;
                        task = std::move(this->tasks_.front());
                        this->tasks_.pop();
                    }

                    task.job();

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex_);
                        active_threads_num_ -= 1;
                    }
                }
            });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock lock{queue_mutex_};
        stop_ = true;
    }

    condition_.notify_all();

    for (auto& t : threads_) {
        t.join();
    }
}

void ThreadPool::addJob(std::function<void()> job)
{
    if (stop_) {
        throw std::runtime_error("Add job to stopped thread pool");
    }

    {
        std::unique_lock lock{queue_mutex_};

        Task task;
        task.job = std::move(job);

        tasks_.push(task);

        if (active_threads_num_ < num_of_thread_) {
            condition_.notify_one();
        }
    }
}

} // namespace San