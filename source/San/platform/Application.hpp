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
     * @brief Prepares the application for execution
     * @param platform The platform the application is being run on
     */
    virtual bool prepare(Platform& platform) { platform_ = &platform; return true; }
    
    /**
     * @brief setup application properties
     */
    virtual void setup() {}
    /**
     * @brief Updates the application
     * @param delta_time The time since the last update
     */
    virtual void update(float delta_time);

    /**
     * @brief Handles cleaning up the application
     */
    virtual void finish() {}

    /**
     * @brief Handles resizing of the window
     * @param width New width of the window
     * @param height New height of the window
     */
    virtual bool resize(const uint32_t width, const uint32_t height) { return true; }

    /**
     * @brief Handles input events of the window
     * @param input_event The input event object
     */
    virtual void input_event(const InputEvent& input_event) {}

    const std::string& get_name() const { return name_; }

    void set_name(const std::string& name) { name_ = name;}

protected:
    float fps_{0.0f};

    float frame_time_{0.0f};        // In ms

    uint32_t frame_count_{0};

    uint32_t last_frame_count_{0};

    Platform* platform_ = nullptr;

    std::string name_{"Sample Application"};
};

} // namespace San

