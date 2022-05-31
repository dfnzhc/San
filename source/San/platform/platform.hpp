//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

#include <San/base/timer.hpp>
#include "San/platform/window.hpp"
#include "San/platform/input_events.hpp"
#include "San/platform/Application.hpp"

namespace San {

enum class ExitCode
{
    Success = 0, /* 程序按预期退出 */
    FatalError   /* 程序发生了错误、异常 */
};

class Platform
{
public:
    Platform() = default;

    virtual ~Platform() = default;

    /**
     * @brief 初始化 platform
     * @return 
     */
    virtual ExitCode initialize();

    /**
     * @brief 程序的主循环，如果有必要应该直接在子类进行重写覆盖
     * @return 程序的推出代码
     */
    ExitCode mainLoop();

    /**
     * @brief 更新所有部件
     */
    void update();

    /**
     * @brief 终止程序
     * @param code 用来决定程序应该怎么样终止
     */
    virtual void terminate(ExitCode code);

    /**
     * @brief 请求关闭程序
     */
    virtual void close();

    /**
     * @brief 返回程序的工作目录
     */
    static const std::string& getWorkDirectory() { return work_directory_; }

    virtual void resize(uint32_t width, uint32_t height);

    virtual void inputEvent(const InputEvent& input_event);

    Window* getWindow() { return window_.get(); }

    static void setWorkDirectory(const std::string& dir) { work_directory_ = dir; }

    void setWindowProperties(const Window::OptionalProperties& properties);

    static const uint32_t MIN_WINDOW_WIDTH;
    static const uint32_t MIN_WINDOW_HEIGHT;

    virtual void setApplication(Application* app) = 0;

protected:
    std::unique_ptr<Window> window_ = nullptr;
    Application* application_ = nullptr;

    virtual void createWindow(const Window::Properties& properties) = 0;

    Window::Properties window_properties_;
    bool close_requested_ = false;

private:
    Timer timer_{};

    static std::string work_directory_;
};

} // namespace San
