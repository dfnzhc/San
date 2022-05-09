//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

namespace Yuan {

class Window
{
public:
    struct Extent
    {
        uint32_t width;
        uint32_t height;
    };

    struct OptionalExtent
    {
        std::optional<uint32_t> width;
        std::optional<uint32_t> height;
    };

    enum class Mode
    {
        Headless,
        Fullscreen,
        FullscreenBorderless,
        Default
    };

    enum class Vsync
    {
        OFF,
        ON,
        Default
    };

    struct OptionalProperties
    {
        std::optional<std::string> title;
        std::optional<Mode> mode;
        std::optional<bool> resizable;
        std::optional<Vsync> vsync;
        OptionalExtent extent;
    };

    struct Properties
    {
        std::string title = "";
        Mode mode = Mode::Default;
        bool resizable = true;
        Vsync vsync = Vsync::Default;
        Extent extent = {1280, 720};
    };

    Window(Properties properties);

    virtual ~Window() = default;

    /**
     * @brief Checks if the window should be closed
     */
    virtual bool shouldClose() = 0;

    /**
     * @brief Handles the processing of all underlying window events
     */
    virtual void processEvents() {}

    /**
     * @brief Requests to close the window
     */
    virtual void close() = 0;

    /**
     * @return The dot-per-inch scale factor
     */
    virtual float getDpiFactor() const = 0;

    /**
     * @return The scale factor for systems with heterogeneous window and pixel coordinates
     */
    virtual float getContentScaleFactor() const { return 1.0f; }

    /**
     * @brief Attempt to resize the window - not gauranteed to change
     * 
     * @param extent The preferred window extent
     * @return Extent The new window extent
     */
    Extent resize(const Extent& extent);

    const Extent& getExtent() const { return properties_.extent; }

    Mode getWindowMode() const { return properties_.mode; }

protected:
    Properties properties_;
};

} // namespace Yuan
