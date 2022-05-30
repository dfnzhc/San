//
// Created by 秋鱼 on 2022/5/10.
//

#include "win_platform.hpp"
#include "glfw_window.hpp"

namespace San {

void WinPlatform::createWindow(const Window::Properties& properties)
{
    window_ = std::make_unique<GLFW_Window>(this, properties);
}

void WinPlatform::setApplication(Application* app)
{
    application_ = app;
    application_->prepare(*this);
}

} // namespace San