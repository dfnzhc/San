//
// Created by 秋鱼 on 2022/5/10.
//

#pragma once

#include "San/platform/input_events.hpp"

namespace San {

class Window;
class Platform;

class Application
{
public:
    Application() = default;

    virtual ~Application() = default;

    /**
     * @brief 准备 app 运行所必要的部件
     * @param platform app 所运行的系统
     */
    virtual bool prepare(Platform& platform) { platform_ = &platform; return true; }
    
    /**
     * @brief 设置 app 属性
     */
    virtual void setup() {}
    /**
     * @brief 更新 app
     * @param delta_time 与上次更新间的间隔
     */
    virtual void update(float delta_time);

    /**
     * @brief app 运行，执行清除操作
     */
    virtual void finish() {}

    /**
     * @brief 处理窗口大小改变的事件
     * @param width 新窗口的宽
     * @param height 新窗口的高
     */
    virtual bool resize(const uint32_t width, const uint32_t height) { return true; }

    /**
     * @brief 处理输入事件
     * @param input_event 输入事件对象
     */
    virtual void input_event(const InputEvent& input_event) {}

    std::string_view get_name() const { return name_; }

protected:
    float fps_{0.0f};

    float frame_time_{0.0f};        // In ms

    uint32_t frame_count_{0};

    uint32_t last_frame_count_{0};

    Platform* platform_ = nullptr;

    std::string name_{"Sample Application"};
};

} // namespace San

