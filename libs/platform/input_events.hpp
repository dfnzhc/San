//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

#include "keycode.hpp"
namespace Yuan {

enum class EventType
{
    Keyboard, Mouse
};

struct InputEvent
{
    EventType type;
};

struct KeyInputEvent : public InputEvent
{
    KeyCode code;
    KeyAction action;
};

struct MouseInputEvent : public InputEvent
{
    KeyCode code;
    KeyAction action;
    
    float pox_x = 0.0f;
    float pox_y = 0.0f;
};

} // namespace Yuan