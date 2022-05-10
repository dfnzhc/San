﻿//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

#include "window.hpp"
#include "platform.hpp"

struct GLFWwindow;

namespace Yuan {

class GLFW_Window : public Window
{
public:
    GLFW_Window(Platform *platform, const Window::Properties &properties);

	virtual ~GLFW_Window();

	bool shouldClose() override;

	void processEvents() override;

	void close() override;

	float getDpiFactor() const override;

	float getContentScaleFactor() const override;
    
private:
    void setGLFWCallback();
    
    
    GLFWwindow* handle_ = nullptr;
};

} // namespace Yuan
