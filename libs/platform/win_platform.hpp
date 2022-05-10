﻿//
// Created by 秋鱼 on 2022/5/10.
//

#pragma once

#include "platform/platform.hpp"

namespace Yuan {

class WinPlatform : public Platform
{
public:
    WinPlatform() = default;
    
    virtual ~WinPlatform() = default;
    
protected:
	virtual void createWindow(const Window::Properties &properties) override;
};

} // namespace Yuan
