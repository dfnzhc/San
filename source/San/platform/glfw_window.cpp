﻿//
// Created by 秋鱼 on 2022/5/9.
//

#include "glfw_window.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "San/base/common.hpp"
#include "San/base/logger.hpp"
#include "input_events.hpp"

namespace San {

inline KeyCode TranslateKeyCode(int key)
{
    static const std::unordered_map<int, KeyCode> key_lookup =
        {
            {GLFW_KEY_SPACE, KeyCode::Space},
            {GLFW_KEY_APOSTROPHE, KeyCode::Apostrophe},
            {GLFW_KEY_COMMA, KeyCode::Comma},
            {GLFW_KEY_MINUS, KeyCode::Minus},
            {GLFW_KEY_PERIOD, KeyCode::Period},
            {GLFW_KEY_SLASH, KeyCode::Slash},
            {GLFW_KEY_0, KeyCode::_0},
            {GLFW_KEY_1, KeyCode::_1},
            {GLFW_KEY_2, KeyCode::_2},
            {GLFW_KEY_3, KeyCode::_3},
            {GLFW_KEY_4, KeyCode::_4},
            {GLFW_KEY_5, KeyCode::_5},
            {GLFW_KEY_6, KeyCode::_6},
            {GLFW_KEY_7, KeyCode::_7},
            {GLFW_KEY_8, KeyCode::_8},
            {GLFW_KEY_9, KeyCode::_9},
            {GLFW_KEY_SEMICOLON, KeyCode::Semicolon},
            {GLFW_KEY_EQUAL, KeyCode::Equal},
            {GLFW_KEY_A, KeyCode::A},
            {GLFW_KEY_B, KeyCode::B},
            {GLFW_KEY_C, KeyCode::C},
            {GLFW_KEY_D, KeyCode::D},
            {GLFW_KEY_E, KeyCode::E},
            {GLFW_KEY_F, KeyCode::F},
            {GLFW_KEY_G, KeyCode::G},
            {GLFW_KEY_H, KeyCode::H},
            {GLFW_KEY_I, KeyCode::I},
            {GLFW_KEY_J, KeyCode::J},
            {GLFW_KEY_K, KeyCode::K},
            {GLFW_KEY_L, KeyCode::L},
            {GLFW_KEY_M, KeyCode::M},
            {GLFW_KEY_N, KeyCode::N},
            {GLFW_KEY_O, KeyCode::O},
            {GLFW_KEY_P, KeyCode::P},
            {GLFW_KEY_Q, KeyCode::Q},
            {GLFW_KEY_R, KeyCode::R},
            {GLFW_KEY_S, KeyCode::S},
            {GLFW_KEY_T, KeyCode::T},
            {GLFW_KEY_U, KeyCode::U},
            {GLFW_KEY_V, KeyCode::V},
            {GLFW_KEY_W, KeyCode::W},
            {GLFW_KEY_X, KeyCode::X},
            {GLFW_KEY_Y, KeyCode::Y},
            {GLFW_KEY_Z, KeyCode::Z},
            {GLFW_KEY_LEFT_BRACKET, KeyCode::LeftBracket},
            {GLFW_KEY_BACKSLASH, KeyCode::Backslash},
            {GLFW_KEY_RIGHT_BRACKET, KeyCode::RightBracket},
            {GLFW_KEY_GRAVE_ACCENT, KeyCode::GraveAccent},
            {GLFW_KEY_ESCAPE, KeyCode::Escape},
            {GLFW_KEY_ENTER, KeyCode::Enter},
            {GLFW_KEY_TAB, KeyCode::Tab},
            {GLFW_KEY_BACKSPACE, KeyCode::Backspace},
            {GLFW_KEY_INSERT, KeyCode::Insert},
            {GLFW_KEY_DELETE, KeyCode::DelKey},
            {GLFW_KEY_RIGHT, KeyCode::Right},
            {GLFW_KEY_LEFT, KeyCode::Left},
            {GLFW_KEY_DOWN, KeyCode::Down},
            {GLFW_KEY_UP, KeyCode::Up},
            {GLFW_KEY_PAGE_UP, KeyCode::PageUp},
            {GLFW_KEY_PAGE_DOWN, KeyCode::PageDown},
            {GLFW_KEY_HOME, KeyCode::Home},
            {GLFW_KEY_END, KeyCode::End},
            {GLFW_KEY_CAPS_LOCK, KeyCode::CapsLock},
            {GLFW_KEY_SCROLL_LOCK, KeyCode::ScrollLock},
            {GLFW_KEY_NUM_LOCK, KeyCode::NumLock},
            {GLFW_KEY_PRINT_SCREEN, KeyCode::PrintScreen},
            {GLFW_KEY_PAUSE, KeyCode::Pause},
            {GLFW_KEY_F1, KeyCode::F1},
            {GLFW_KEY_F2, KeyCode::F2},
            {GLFW_KEY_F3, KeyCode::F3},
            {GLFW_KEY_F4, KeyCode::F4},
            {GLFW_KEY_F5, KeyCode::F5},
            {GLFW_KEY_F6, KeyCode::F6},
            {GLFW_KEY_F7, KeyCode::F7},
            {GLFW_KEY_F8, KeyCode::F8},
            {GLFW_KEY_F9, KeyCode::F9},
            {GLFW_KEY_F10, KeyCode::F10},
            {GLFW_KEY_F11, KeyCode::F11},
            {GLFW_KEY_F12, KeyCode::F12},
            {GLFW_KEY_KP_0, KeyCode::KP_0},
            {GLFW_KEY_KP_1, KeyCode::KP_1},
            {GLFW_KEY_KP_2, KeyCode::KP_2},
            {GLFW_KEY_KP_3, KeyCode::KP_3},
            {GLFW_KEY_KP_4, KeyCode::KP_4},
            {GLFW_KEY_KP_5, KeyCode::KP_5},
            {GLFW_KEY_KP_6, KeyCode::KP_6},
            {GLFW_KEY_KP_7, KeyCode::KP_7},
            {GLFW_KEY_KP_8, KeyCode::KP_8},
            {GLFW_KEY_KP_9, KeyCode::KP_9},
            {GLFW_KEY_KP_DECIMAL, KeyCode::KP_Decimal},
            {GLFW_KEY_KP_DIVIDE, KeyCode::KP_Divide},
            {GLFW_KEY_KP_MULTIPLY, KeyCode::KP_Multiply},
            {GLFW_KEY_KP_SUBTRACT, KeyCode::KP_Subtract},
            {GLFW_KEY_KP_ADD, KeyCode::KP_Add},
            {GLFW_KEY_KP_ENTER, KeyCode::KP_Enter},
            {GLFW_KEY_KP_EQUAL, KeyCode::KP_Equal},
            {GLFW_KEY_LEFT_SHIFT, KeyCode::LeftShift},
            {GLFW_KEY_LEFT_CONTROL, KeyCode::LeftControl},
            {GLFW_KEY_LEFT_ALT, KeyCode::LeftAlt},
            {GLFW_KEY_RIGHT_SHIFT, KeyCode::RightShift},
            {GLFW_KEY_RIGHT_CONTROL, KeyCode::RightControl},
            {GLFW_KEY_RIGHT_ALT, KeyCode::RightAlt},
        };

    auto key_it = key_lookup.find(key);

    if (key_it == key_lookup.end()) {
        return KeyCode::Unknown;
    }

    return key_it->second;
}

inline KeyAction TranslateKeyAction(int action)
{
    if (action == GLFW_PRESS) {
        return KeyAction::Press;
    } else if (action == GLFW_RELEASE) {
        return KeyAction::Release;
    } else if (action == GLFW_REPEAT) {
        return KeyAction::Repeat;
    }

    return KeyAction::Unknown;
}

inline MouseButton TranslateMouseButton(int button)
{
    if (button < GLFW_MOUSE_BUTTON_6) {
        return static_cast<MouseButton>(button);
    }

    return MouseButton::Unknown;
}

inline MouseAction TranslateMouseAction(int action)
{
    if (action == GLFW_PRESS) {
        return MouseAction::Press;
    } else if (action == GLFW_RELEASE) {
        return MouseAction::Release;
    }

    return MouseAction::Unknown;
}

GLFW_Window::GLFW_Window(Platform* platform, const Window::Properties& properties)
    : Window(properties)
{
    if (!glfwInit()) {
        throw std::runtime_error("GLFW couldn't be initialized.");
    }

    glfwSetErrorCallback([](int error, const char* description)
                         {
                             LOG_ERROR("GLFW Error (code {}): {}", error, description);
                         });

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    switch (properties.mode) {
        case Window::Mode::Fullscreen: {
            auto* monitor = glfwGetPrimaryMonitor();
            const auto* mode = glfwGetVideoMode(monitor);
            handle_ = glfwCreateWindow(mode->width, mode->height, properties.title.c_str(), monitor, nullptr);
            break;
        }

        case Window::Mode::FullscreenBorderless: {
            auto* monitor = glfwGetPrimaryMonitor();
            const auto* mode = glfwGetVideoMode(monitor);
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            handle_ = glfwCreateWindow(mode->width, mode->height, properties.title.c_str(), monitor, nullptr);
            break;
        }

        default:
            handle_ = glfwCreateWindow(properties.extent.width,
                                       properties.extent.height,
                                       properties.title.c_str(),
                                       nullptr,
                                       nullptr);
            break;
    }

    resize(Extent{properties.extent.width, properties.extent.height});

    if (!handle_) {
        throw std::runtime_error("Couldn't create glfw window.");
    }

    glfwSetWindowUserPointer(handle_, platform);

    setGLFWCallback();

    LOG_INFO("Create GLFW window successfully.");
}

GLFW_Window::~GLFW_Window()
{
    glfwTerminate();
}

bool GLFW_Window::shouldClose()
{
    return glfwWindowShouldClose(handle_);
}

void GLFW_Window::processEvents()
{
    glfwPollEvents();
}

void GLFW_Window::close()
{
    Window::processEvents();
}

float GLFW_Window::getDpiFactor() const
{
    auto primary_monitor = glfwGetPrimaryMonitor();
    auto vidmode = glfwGetVideoMode(primary_monitor);

    int width_mm, height_mm;
    glfwGetMonitorPhysicalSize(primary_monitor, &width_mm, &height_mm);

    // As suggested by the GLFW monitor guide
    static const float inch_to_mm = 25.0f;
    static const float win_base_density = 96.0f;

    auto dpi = static_cast<uint32_t>(vidmode->width / (width_mm / inch_to_mm));
    auto dpi_factor = dpi / win_base_density;
    return dpi_factor;
}

float GLFW_Window::getContentScaleFactor() const
{
    int fb_width, fb_height;
    glfwGetFramebufferSize(handle_, &fb_width, &fb_height);
    int win_width, win_height;
    glfwGetWindowSize(handle_, &win_width, &win_height);

    // We could return a 2D result here instead of a scalar,
    // but non-uniform scaling is very unlikely, and would
    // require significantly more changes in the IMGUI integration
    return static_cast<float>(fb_width) / win_width;
}

void GLFW_Window::setGLFWCallback()
{
    glfwSetWindowCloseCallback(handle_, [](GLFWwindow* window)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    });

    glfwSetWindowSizeCallback(handle_, [](GLFWwindow* window, int width, int height)
    {
        if (auto platform = reinterpret_cast<Platform*>(glfwGetWindowUserPointer(window))) {
            platform->resize(width, height);
        }
    });

    glfwSetKeyCallback(handle_, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
    {
        KeyCode key_code = TranslateKeyCode(key);
        KeyAction key_action = TranslateKeyAction(action);

        if (auto platform = reinterpret_cast<Platform*>(glfwGetWindowUserPointer(window))) {
            platform->inputEvent(KeyInputEvent{key_code, key_action});
        }
    });

    glfwSetCursorPosCallback(handle_, [](GLFWwindow* window, double xpos, double ypos)
    {
        if (auto* platform = reinterpret_cast<Platform*>(glfwGetWindowUserPointer(window))) {
            auto* glfwWindow = reinterpret_cast<GLFW_Window*>(platform->getWindow());

            MouseButton button = glfwWindow->getMouseButton();
            MouseAction action = MouseAction::Move;
            if (button != MouseButton::Unknown) {
                action = MouseAction::PressedMove;
            }
            
            platform->inputEvent(MouseInputEvent{
                button,
                action,
                static_cast<float>(xpos),
                static_cast<float>(ypos)});
        }
    });

    glfwSetMouseButtonCallback(handle_, [](GLFWwindow* window, int button, int action, int /*mods*/)
    {
        auto mouse_action = TranslateMouseAction(action);
        auto mouse_button = TranslateMouseButton(button);

        if (auto* platform = reinterpret_cast<Platform*>(glfwGetWindowUserPointer(window))) {
            auto* glfwWindow = reinterpret_cast<GLFW_Window*>(platform->getWindow());

            if (mouse_action == MouseAction::Press) {
                glfwWindow->setMouseButton(mouse_button);
            } else {
                glfwWindow->setMouseButton(MouseButton::Unknown);
            }

            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            platform->inputEvent(MouseInputEvent{
                mouse_button,
                mouse_action,
                static_cast<float>(xpos),
                static_cast<float>(ypos)});
        }
    });

    glfwSetScrollCallback(handle_, [](GLFWwindow* window, double xscroll, double yscroll)
    {
        if (auto* platform = reinterpret_cast<Platform*>(glfwGetWindowUserPointer(window))) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            platform->inputEvent(MouseInputEvent{
                MouseButton::Unknown,
                MouseAction::Scroll,
                static_cast<float>(xpos),
                static_cast<float>(ypos),
                static_cast<float>(yscroll)});
        }
    });
}

} // namespace San