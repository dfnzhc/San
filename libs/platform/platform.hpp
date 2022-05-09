//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

#include <timer.hpp>
#include "window.hpp"
#include "input_events.hpp"
namespace Yuan {
enum class ExitCode
{
    Success = 0, /* App executed as expected */
    Help,        /* App should show help */
    Close,       /* App has been requested to close at initialization */
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
    static const std::string& getWorkDirectory();

    /**
     * @brief Returns the suitable directory for temporary files from the environment variables set in the system
     * @returns The path to the temp folder on the system
     */
    static const std::string& getTempDirectory();

    /**
     * @return The VkInstance extension name for the platform
     */
    virtual const char* get_surface_extension() = 0;

    virtual void resize(uint32_t width, uint32_t height);

    virtual void inputEvent(const InputEvent& input_event);

    Window& getWindow();

    static void setWorkDirectory(const std::string& dir);

    static void setTempDirectory(const std::string& dir);

    void disableInputProcessing();

    void setWindowProperties(const Window::OptionalProperties& properties);

    static const uint32_t MIN_WINDOW_WIDTH;
    static const uint32_t MIN_WINDOW_HEIGHT;

protected:
    std::unique_ptr<Window> window{nullptr};

    virtual void createWindow(const Window::Properties& properties) = 0;

    void onUpdate(float delta_time);
    void onPlatformClose();

    Window::Properties window_properties;           /* Source of truth for window state */
    bool process_input_events = true;               /* App should continue processing input events */
    bool close_requested = false;                   /* Close requested */

private:
    Timer timer;

    static std::string temp_directory;
    static std::string work_directory;
};

} // namespace Yuan
