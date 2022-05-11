//
// Created by 秋鱼 on 2022/5/10.
//

#include <logger.hpp>
#include "Application.hpp"

namespace Yuan {

void Application::update(float delta_time)
{
    fps_        = 1.0f / delta_time;
    frame_time_ = delta_time * 1000.0f;
    
//    LOG_INFO("[APP] update fps: {}", fps_);
}

} // namespace Yuan