//
// Created by 秋鱼 on 2022/6/19.
//

#pragma once

namespace San {

// 每个任务都是通过应用程序线程使用 Async 去调用的。
// 为了防止上下文切换，需要将运行线程的数量限制在内核的数量上，通过一个全局计数器可以跟踪运行线程的数量。
// 当线程正在运行一个任务时，计数器会递增，当它结束时递减。
// 当一个线程进入等待模式，计数器也会递减，而当一个线程发出请求并且有一个核心可以恢复时，计数器增加。
// 如果所有内核都繁忙，应用程序的线程就会进入等待状态，以防止产生更多的线程。

class Sync
{
public:
    /**
     * @brief 计数器加一
     */
    uint16_t inc()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        count_ += 1;

        return count_;
    }

    /**
     * @brief 计数器减一，如果计数器减到 0， 那么唤醒所有等待条件变量的线程
     */
    uint16_t dec()
    {
        std::unique_lock<std::mutex> lock(mutex_);

        count_ -= 1;
        if (count_ == 0) {
            condition_.notify_all();
        }

        return count_;
    }

    /**
     * @brief 获取当前的计数器值
     */
    uint16_t get()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return count_;
    }

    /**
     * @brief 重置计数器到 0，并且唤醒所有等待条件变量的线程
     */
    void reset()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        count_ = 0;
        condition_.notify_all();
    }

    /**
     * @brief 循环等待计数器的值变成 0
     */
    void wait()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ != 0) {
            condition_.wait(lock);
        }
    }

private:
    uint16_t count_ = 0;
    std::mutex mutex_{};
    std::condition_variable condition_{};
};

class AsyncTask
{
public:
    AsyncTask(std::function<void()> job, Sync& sync);

    static void wait(Sync& sync);
    void stop();

private:
    Sync* sync_ = nullptr;
    std::function<void()> job_;
    std::unique_ptr<std::thread> thread_ = nullptr;

    inline static uint16_t MaxThreads = std::thread::hardware_concurrency();
    inline static std::mutex mutex_{};
    inline static std::condition_variable condition_{};
    inline static uint16_t active_threads_num_ = 0;
};

class AsyncPool
{
public:
    ~AsyncPool();
    
    void addAsyncTask(const std::function<void()>& job, Sync& sync);
    void flush();
    
private:
    std::vector<std::unique_ptr<AsyncTask>> tasks_;
};

} // namespace San
