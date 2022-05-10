//
// Created by 秋鱼 on 2022/5/10.
//

#include "win_platform.hpp"
#include "glfw_window.hpp"

namespace Yuan {

void WinPlatform::createWindow(const Window::Properties& properties)
{
    window_ = std::make_unique<GLFW_Window>(this, properties);
}

} // namespace Yuan