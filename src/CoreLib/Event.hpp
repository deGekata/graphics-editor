#ifndef EVENT_HPP
#define EVENT_HPP

#include "Utilities.hpp"

enum class EventType {
    // KEYDOWN,
    // KEYUP,
    KEYBOARD,
    // TEXTEDITING,
    // TEXTINPUT,
    MOUSEMOTION,
    MOUSE_ENTER,
    MOUSE_LEAVE,
    MOUSEBUTTONDOWN,
    MOUSEBUTTONUP,
    MOUSEWHEEL,
    UNKNOWN
};


enum class MouseButton;
enum class ButtonState;
enum class KeyboardButton;


struct MouseButtonEvent {
    int32_t x = 0, y = 0;
    uint8_t clicks = 0;
    MouseButton button;
    ButtonState state;
};

struct MouseMotionEvent {
    int32_t x = 0, y = 0;
    Point pos = {0, 0};
    Point rel_pos = {0, 0};
};

struct KeyboardEvent {
    ButtonState state;
    KeyboardButton button;
};

class Event_;

class Event {
private:
    Event_* rsp_ = NULL;
public:
    EventType type = EventType::UNKNOWN;
    
    union {
        MouseMotionEvent mouse_motion;
        MouseButtonEvent mouse_button;
        KeyboardEvent   keyboard;
    };
    bool is_processed_ = false;
    // static void connect()
};

#endif