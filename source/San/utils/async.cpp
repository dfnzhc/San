//
// Created by 秋鱼 on 2022/6/20.
//

#include "async.hpp"

#include <utility>

namespace San {

AsyncTask::AsyncTask(std::function<void()> job, Sync& sync) : job_{std::move(job)}, sync_{&sync}
{
    sync_->inc();

    {
        std::unique_lock lock{mutex_};

        while (active_threads_num_ >= MaxThreads) {
            condition_.wait(lock);
        }

        active_threads_num_ += 1;
    }

    thread_ = std::make_unique<std::thread>(
        [this]
        {
            job_();
            {
                std::lock_guard lock{mutex_};

                active_threads_num_ -= 1;
            }

            condition_.notify_one();
            sync_->dec();
        });
}

void AsyncTask::wait(Sync& sync)
{
    if (sync.get() == 0) {
        return;
    }

    {
        std::lock_guard lock{mutex_};
        active_threads_num_ -= 1;
    }

    condition_.notify_one();

    sync.wait();

    {
        std::unique_lock lock{mutex_};

        condition_.wait(lock,
                        [] { return active_threads_num_ < MaxThreads; });

        active_threads_num_ += 1;
    }
}

void AsyncTask::stop()
{
    thread_->join();
}

AsyncPool::~AsyncPool()
{
    flush();
}

void AsyncPool::addAsyncTask(const std::function<void()>& job, Sync& sync)
{
    tasks_.emplace_back(std::make_unique<AsyncTask>(job, sync));
}

void AsyncPool::flush()
{
    for (auto& task : tasks_) {
        task->stop();
    }
    tasks_.clear();
}

} // namespace San