﻿//
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
    Success = 0, /* App executed as expected */
    FatalError   /* App encountered an unexpected error */
};

class Platform
{
public:
    Platform() = default;

    virtual ~Platform() = default;

    /**
     * @brief Initialize the platform
     * @return An exit code representing the outcome of initialization
     */
    virtual ExitCode initialize();

    /**
     * @brief Handles the main loop of the platform
     * This should be overriden if a platform requires a specific main loop setup.
     * @return An exit code representing the outcome of the loop
     */
    ExitCode mainLoop();

    /**
     * @brief Runs the application for one frame
     */
    void update();

    /**
     * @brief Terminates the platform and the application
     * @param code Determines how the platform should exit
     */
    virtual void terminate(ExitCode code);

    /**
     * @brief Requests to close the platform at the next available point
     */
    virtual void close();

    /**
     * @brief Returns the working directory of the application set by the platform
     * @returns The path to the working directory
     */
    static const std::string& getWorkDirectory() { return work_directory_; }

    /**
     * @brief Returns the suitable directory for temporary files from the environment variables set in the system
     * @returns The path to the temp folder on the system
     */
    static const std::string& getTempDirectory() { return temp_directory_; }

    virtual void resize(uint32_t width, uint32_t height);

    virtual void inputEvent(const InputEvent& input_event);

    Window* getWindow() { return window_.get(); }

    static void setWorkDirectory(const std::string& dir) { work_directory_ = dir; }

    static void setTempDirectory(const std::string& dir) { temp_directory_ = dir; }

    void disableInputProcessing() { process_input_events_ = false; }

    void setWindowProperties(const Window::OptionalProperties& properties);

    static const uint32_t MIN_WINDOW_WIDTH;
    static const uint32_t MIN_WINDOW_HEIGHT;
    
    virtual void setApplication(Application* app) = 0;

protected:
    std::unique_ptr<Window> window_ = nullptr;
    Application* application_ = nullptr;

    virtual void createWindow(const Window::Properties& properties) = 0;

    Window::Properties window_properties_;           /* Source of truth for window state */
    bool process_input_events_ = true;               /* App should continue processing input events */
    bool close_requested_ = false;                   /* Close requested */
    
private:
    Timer timer_;

    static std::string temp_directory_;
    static std::string work_directory_;
};

} // namespace San