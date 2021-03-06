//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

#include "San/platform/keycode.hpp"

namespace San {

enum class EventType
{
    Keyboard, Mouse
};

struct InputEvent
{
    InputEvent(EventType type) : type{type} {};

    EventType type;
};

struct KeyInputEvent : public InputEvent
{
    KeyInputEvent(KeyCode key, KeyAction action)
        : InputEvent{EventType::Keyboard}, code{key}, action{action} {};

    KeyCode code;
    KeyAction action;

    inline bool isEvent(KeyCode c, KeyAction a) const
    {
        return code == c && action == a;
    }
};

struct MouseInputEvent : public InputEvent
{
    MouseInputEvent(MouseButton button, MouseAction action, float x, float y, float dir = 0)
        : InputEvent{EventType::Mouse}, button{button}, action{action}, pos_x{x}, pos_y{y}, scroll_dir{dir} {};

    MouseButton button;
    MouseAction action;

    float pos_x = 0.0f;
    float pos_y = 0.0f;
    float scroll_dir = 0;

    inline bool isEvent(MouseButton b, MouseAction a) const
    {
        return button == b && action == a;
    }
};

} // namespace San