//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

#include "San/platform/window.hpp"
#include "San/platform/platform.hpp"

struct GLFWwindow;

namespace San {

class GLFW_Window : public Window
{
public:
    GLFW_Window(Platform* platform, const Window::Properties& properties);

    ~GLFW_Window() override;

    bool shouldClose() override;

    void processEvents() override;

    void close() override;

    float getDpiFactor() const override;

    float getContentScaleFactor() const override;

    GLFWwindow* getGLFWHandle() const { return handle_; }
private:
    void setGLFWCallback();
    MouseButton getMouseButton() const { return pressedMouseButton; }
    void setMouseButton(MouseButton button) { pressedMouseButton = button; }

    GLFWwindow* handle_ = nullptr;
    MouseButton pressedMouseButton = MouseButton::Unknown;
};

} // namespace San
