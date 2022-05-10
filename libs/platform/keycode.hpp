//
// Created by 秋鱼 on 2022/5/9.
//

#pragma once

namespace Yuan {

enum class KeyAction
{
    Press,
    Release,
    Repeat,
    Unknown
};

inline std::string GetActionString(KeyAction action)
{
    if (action == KeyAction::Press) {
        return "Press";
    }

    if (action == KeyAction::Release) {
        return "Release";
    }

    if (action == KeyAction::Repeat) {
        return "Repeat";
    }

    return "Unknown";
}

enum class KeyCode
{
    Unknown,
    Space,
    Apostrophe, /* ' */
    Comma,      /* , */
    Minus,      /* - */
    Period,     /* . */
    Slash,      /* / */
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    Semicolon, /* ; */
    Equal,     /* = */
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    LeftBracket,  /* [ */
    Backslash,    /* \ */
    RightBracket, /* ] */
    GraveAccent,  /* ` */
    Escape,
    Enter,
    Tab,
    Backspace,
    Insert,
    DelKey,
    Right,
    Left,
    Down,
    Up,
    PageUp,
    PageDown,
    Home,
    End,
    Back,
    CapsLock,
    ScrollLock,
    NumLock,
    PrintScreen,
    Pause,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    KP_0,
    KP_1,
    KP_2,
    KP_3,
    KP_4,
    KP_5,
    KP_6,
    KP_7,
    KP_8,
    KP_9,
    KP_Decimal,
    KP_Divide,
    KP_Multiply,
    KP_Subtract,
    KP_Add,
    KP_Enter,
    KP_Equal,
    LeftShift,
    LeftControl,
    LeftAlt,
    RightShift,
    RightControl,
    RightAlt
};

enum class KeyMod
{
    SHIFT,
    CONTROL,
    ALT,
    SUPER,
};

enum class MouseButton
{
    Left,
    Right,
    Middle,
    Back,
    Forward,
    Unknown
};

inline std::string GetButtonString(MouseButton button)
{
    if (button == MouseButton::Left) {
        return "Left";
    }

    if (button == MouseButton::Right) {
        return "Right";
    }

    if (button == MouseButton::Middle) {
        return "Middle";
    }

    if (button == MouseButton::Back) {
        return "Back";
    }

    if (button == MouseButton::Forward) {
        return "Forward";
    }

    return "Unknown";
}

enum class MouseAction
{
    Press,
    Release,
    Move,
    Scroll,
    Unknown
};

inline std::string GetActionString(MouseAction action)
{
    if (action == MouseAction::Press) {
        return "Press";
    }

    if (action == MouseAction::Release) {
        return "Release";
    }

    if (action == MouseAction::Move) {
        return "Move";
    }

    if (action == MouseAction::Scroll) {
        return "Scroll";
    }

    return "Unknown";
}

} // namespace Yuan