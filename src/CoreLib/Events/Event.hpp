#ifndef EVENT_HPP
#define EVENT_HPP

#include "Utilities/Utilities.hpp"
#include "KeyBoardCodes.hpp"
#include "Mouse.hpp"

enum class EventType {
    KEYDOWN,
    KEYUP,
    // KEYBOARD,
    // TEXTEDITING,
    // TEXTINPUT,
    QUIT,
    MOUSEMOTION,
    MOUSE_ENTER,
    MOUSE_LEAVE,
    MOUSEBUTTONDOWN,
    MOUSEBUTTONUP,
    MOUSEWHEEL,
    UNKNOWN
};

enum ButtonState {
    BUTTON_DOWN = 0,
    BUTTON_UP   = 1,
};

struct MouseButtonEvent {
    Point pos = {0, 0};
    uint8_t clicks = 0;
    MouseButton button;
    ButtonState state;
};

enum class MouseMotionType {
    FULL,
    ONLY_ENTER,
    ONLY_LEAVE
};

struct MouseMotionEvent {
    Point pos = {0, 0};
    Point rel_pos = {0, 0};
};

struct KeyboardEvent {
    ButtonState state;
    Keysym key;
};

class Event {
private:
    // Event_* rsp_ = NULL;
public:
    Event() {}
    EventType type = EventType::UNKNOWN;
    
    union {
        MouseMotionEvent mouse_motion;
        MouseButtonEvent mouse_button;
        KeyboardEvent   keyboard;
    };
    MouseMotionType mouse_motion_type = MouseMotionType::FULL;
    bool is_processed_ = false;
    // static void connect()
};

bool is_for_text_input(int sym);
#endif