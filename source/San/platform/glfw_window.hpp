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

    virtual ~GLFW_Window();

    bool shouldClose() override;

    void processEvents() override;

    void close() override;

    float getDpiFactor() const override;

    float getContentScaleFactor() const override;

    GLFWwindow* getGlfwWindowHandle() const { return handle_; }
    void setMouseButton(MouseButton button) { pressedMouseButton = button; }
    MouseButton getMouseButton() const { return pressedMouseButton; }

private:
    void setGLFWCallback();

    GLFWwindow* handle_ = nullptr;
    MouseButton pressedMouseButton = MouseButton::Unknown;
};

} // namespace San
