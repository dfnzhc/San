//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

namespace San {

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
        std::string title = "San Window";
        Mode mode = Mode::Default;
        bool resizable = true;
        Vsync vsync = Vsync::Default;
        Extent extent = {1280, 720};
    };

    Window(Properties properties);

    virtual ~Window() = default;

    /**
     * @brief 检查窗口是否应该关闭
     */
    virtual bool shouldClose() = 0;

    /**
     * @brief 处理所有窗口事件
     */
    virtual void processEvents() {}

    /**
     * @brief 请求关闭窗口
     */
    virtual void close() = 0;

    /**
     * @return 窗口的 dpi(dot-per-inch) 属性
     */
    virtual float getDpiFactor() const = 0;

    /**
     * @return 窗口像素的缩放因子，默认是 1
     */
    virtual float getContentScaleFactor() const { return 1.0f; }

    /**
     * @brief 尝试更改窗口大小，可能不会发生
     * 
     * @param extent 要更新的窗口大小
     * @return Extent 更新后的窗口大小
     */
    Extent resize(const Extent& extent);

    const Extent& getExtent() const { return properties_.extent; }
    Mode getWindowMode() const { return properties_.mode; }

protected:
    Properties properties_;
};

} // namespace San
