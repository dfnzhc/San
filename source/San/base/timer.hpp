//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

namespace San {

class Timer
{
public:
    using Seconds = std::ratio<1>;
    using Milliseconds = std::ratio<1, 1000>;
    using Microseconds = std::ratio<1, 1000000>;
    using Nanoseconds = std::ratio<1, 1000000000>;

    // Configure
    using Clock = std::chrono::steady_clock;
    using DefaultResolution = Seconds;

    Timer() :
        start_time_{Clock::now()},
        previous_tick_{Clock::now()}
    {
    }
    
    virtual ~Timer() = default;

    void start()
    {
        if (!running_) {
            running_ = true;
            start_time_ = Clock::now();
        }
    }

    /**
	 * @brief 开始计时, elapsed() 返回现在到上一次 lap() 的时间间隔
	 */
    void lap()
    {
        lapping_ = true;
        lap_time_ = Clock::now();
    }

    /**
	 * @brief 停止计时
	 * @return 返回时钟从 `start()` 到 `stop()` 的时间间隔
	 */    
    template<typename T = DefaultResolution>
    double stop()
    {
        if (!running_) {
            return 0;
        }

        running_ = false;
        lapping_ = false;
        auto duration = std::chrono::duration<double, T>(Clock::now() - start_time_);
        start_time_ = Clock::now();
        lap_time_ = Clock::now();

        return duration.count();
    }

    /**
	 * @brief 如果开始计时，即调用 'lap()' ，那么返回 ‘now()’ 到上一次 'lap()' 的时间间隔；否则返回 ‘now()’ 到 'start()'
	 * @return 两个时间点的间隔 (默认单位：秒)
	 */
    template<typename T = DefaultResolution>
    double elapsed()
    {
        if (!running_) {
            return 0;
        }

        Clock::time_point start = start_time_;

        if (lapping_) {
            start = lap_time_;
        }

        return std::chrono::duration<double, T>(Clock::now() - start).count();
    }

    /**
	 * @brief 返回 ‘now()' 与上一次调用 tick() 的时间间隔
	 * @return 两个时间点的间隔 (默认单位：秒)
	 */
    template<typename T = DefaultResolution>
    double tick()
    {
        auto now = Clock::now();
        auto duration = std::chrono::duration<double, T>(now - previous_tick_);
        previous_tick_ = now;
        return duration.count();
    }

    bool isRunning() const
    {
        return running_;
    }
    
private:
    bool running_ = false;
    bool lapping_ = false;

    Clock::time_point start_time_;
    Clock::time_point lap_time_;
    Clock::time_point previous_tick_;
};

} // namespace San