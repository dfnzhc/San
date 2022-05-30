//
// Created by 秋鱼 on 2022/5/10.
//

#pragma once

#include "San/platform/platform.hpp"

namespace San {

class WinPlatform : public Platform
{
public:
    WinPlatform() = default;
    
    virtual ~WinPlatform() = default;

    virtual void setApplication(Application* app) override;
protected:
	virtual void createWindow(const Window::Properties &properties) override;
};

} // namespace San
