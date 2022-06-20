//
// Created by 秋鱼 on 2022/6/20.
//

#pragma once

namespace San {

struct Task
{
    std::function<void()> job;
};

class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();

    void addJob(std::function<void()> job);

private:
    bool stop_ = false;
    uint16_t num_of_thread_ = std::thread::hardware_concurrency();
    uint16_t active_threads_num_ = 0;

    std::vector<std::thread> threads_;
    std::queue<Task> tasks_;

    std::condition_variable condition_;
    std::mutex queue_mutex_;
};
} // namespace San
