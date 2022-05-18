//
// Created by 秋鱼 on 2022/5/9.
//

#include "platform.hpp"

#include "yuan/base/common.hpp"
#include "yuan/base/logger.hpp"

namespace Yuan {

const uint32_t Platform::MIN_WINDOW_WIDTH = 420;
const uint32_t Platform::MIN_WINDOW_HEIGHT = 320;

std::string Platform::work_directory_ = "";
std::string Platform::temp_directory_ = "";

ExitCode Platform::initialize()
{
    if (application_) {
        window_properties_.title = application_->get_name();
    }

    createWindow(window_properties_);

    if (!window_) {
        LOG_ERROR("Window creation failed!");

        return ExitCode::FatalError;
    }

    return ExitCode::Success;
}

ExitCode Platform::mainLoop()
{
    while (!window_->shouldClose() && !close_requested_) {
        try {
            update();
            window_->processEvents();
        }
        catch (std::exception& e) {
            LOG_ERROR("Error Message: {}", e.what());

            // TODO: handle the exceptions
        }
    }

    return ExitCode::Success;
}

void Platform::update()
{
    [[maybe_unused]]
    auto delta_time = static_cast<float>(timer_.tick<Timer::Seconds>());

    if (application_) {
        application_->update(delta_time);
    }
}

void Platform::terminate(ExitCode code)
{
    if (application_) {
        application_->finish();
    }

    window_.reset();
}

void Platform::close()
{
    if (window_) {
        window_->close();
    }

    close_requested_ = true;
}

void Platform::resize(uint32_t width, uint32_t height)
{
    auto extent = Window::Extent{std::max<uint32_t>(width, MIN_WINDOW_WIDTH),
                                 std::max<uint32_t>(height, MIN_WINDOW_HEIGHT)};
    if (window_) {
        auto actual_extent = window_->resize(extent);

        if (application_) {
            application_->resize(actual_extent.width, actual_extent.height);
        }
    }
}

void Platform::inputEvent(const InputEvent& input_event)
{
    if (process_input_events_ && application_) {
        application_->input_event(input_event);
    }

    if (input_event.type == EventType::Keyboard) {
        const auto& key_event = static_cast<const KeyInputEvent&>(input_event);

        if (key_event.code == KeyCode::Back ||
            key_event.code == KeyCode::Escape) {
            close();
        }

//        LOG_INFO("[Keyboard] key: {}, action: {}", static_cast<int>(key_event.code), GetActionString(key_event.action));
    } else if (input_event.type == EventType::Mouse) {
        [[maybe_unused]] 
        const auto& mouse_event = static_cast<const MouseInputEvent&>(input_event);

//        LOG_INFO("[Mouse] key: {}, action: {} ({}.{} {})",
//                 GetButtonString(mouse_event.button),
//                 GetActionString(mouse_event.action), mouse_event.pos_x, mouse_event.pos_y, mouse_event.scroll_dir);
    }
}

void Platform::setWindowProperties(const Window::OptionalProperties& properties)
{
#define SetProperty(src, dst)                   \
    dst = src.has_value() ? src.value() : dst

    SetProperty(properties.title, window_properties_.title);
    SetProperty(properties.mode, window_properties_.mode);
    SetProperty(properties.resizable, window_properties_.resizable);
    SetProperty(properties.vsync, window_properties_.vsync);
    SetProperty(properties.extent.width, window_properties_.extent.width);
    SetProperty(properties.extent.height, window_properties_.extent.height);

#undef SetProperty
}

} // namespace Yuan
