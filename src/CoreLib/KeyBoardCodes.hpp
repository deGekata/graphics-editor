#ifndef KEYBOARD_CODES_HPP
#define KEYBOARD_CODES_HPP

#include "Scancode.hpp"

#define K_SCANCODE_MASK (1<<30)
#define SCANCODE_TO_KEYCODE(X)  (X | K_SCANCODE_MASK)



enum Keycode {
    K_UNKNOWN = 0,

    K_RETURN = '\r',
    K_ESCAPE = '\x1B',
    K_BACKSPACE = '\b',
    K_TAB = '\t',
    K_SPACE = ' ',
    K_EXCLAIM = '!',
    K_QUOTEDBL = '"',
    K_HASH = '#',
    K_PERCENT = '%',
    K_DOLLAR = '$',
    K_AMPERSAND = '&',
    K_QUOTE = '\'',
    K_LEFTPAREN = '(',
    K_RIGHTPAREN = ')',
    K_ASTERISK = '*',
    K_PLUS = '+',
    K_COMMA = ',',
    K_MINUS = '-',
    K_PERIOD = '.',
    K_SLASH = '/',
    K_0 = '0',
    K_1 = '1',
    K_2 = '2',
    K_3 = '3',
    K_4 = '4',
    K_5 = '5',
    K_6 = '6',
    K_7 = '7',
    K_8 = '8',
    K_9 = '9',
    K_COLON = ':',
    K_SEMICOLON = ';',
    K_LESS = '<',
    K_EQUALS = '=',
    K_GREATER = '>',
    K_QUESTION = '?',
    K_AT = '@',

    K_LEFTBRACKET = '[',
    K_BACKSLASH = '\\',
    K_RIGHTBRACKET = ']',
    K_CARET = '^',
    K_UNDERSCORE = '_',
    K_BACKQUOTE = '`',
    K_a = 'a',
    K_b = 'b',
    K_c = 'c',
    K_d = 'd',
    K_e = 'e',
    K_f = 'f',
    K_g = 'g',
    K_h = 'h',
    K_i = 'i',
    K_j = 'j',
    K_k = 'k',
    K_l = 'l',
    K_m = 'm',
    K_n = 'n',
    K_o = 'o',
    K_p = 'p',
    K_q = 'q',
    K_r = 'r',
    K_s = 's',
    K_t = 't',
    K_u = 'u',
    K_v = 'v',
    K_w = 'w',
    K_x = 'x',
    K_y = 'y',
    K_z = 'z',

    K_CAPSLOCK = SCANCODE_TO_KEYCODE(SCANCODE_CAPSLOCK),

    K_F1 = SCANCODE_TO_KEYCODE(SCANCODE_F1),
    K_F2 = SCANCODE_TO_KEYCODE(SCANCODE_F2),
    K_F3 = SCANCODE_TO_KEYCODE(SCANCODE_F3),
    K_F4 = SCANCODE_TO_KEYCODE(SCANCODE_F4),
    K_F5 = SCANCODE_TO_KEYCODE(SCANCODE_F5),
    K_F6 = SCANCODE_TO_KEYCODE(SCANCODE_F6),
    K_F7 = SCANCODE_TO_KEYCODE(SCANCODE_F7),
    K_F8 = SCANCODE_TO_KEYCODE(SCANCODE_F8),
    K_F9 = SCANCODE_TO_KEYCODE(SCANCODE_F9),
    K_F10 = SCANCODE_TO_KEYCODE(SCANCODE_F10),
    K_F11 = SCANCODE_TO_KEYCODE(SCANCODE_F11),
    K_F12 = SCANCODE_TO_KEYCODE(SCANCODE_F12),

    K_PRINTSCREEN = SCANCODE_TO_KEYCODE(SCANCODE_PRINTSCREEN),
    K_SCROLLLOCK = SCANCODE_TO_KEYCODE(SCANCODE_SCROLLLOCK),
    K_PAUSE = SCANCODE_TO_KEYCODE(SCANCODE_PAUSE),
    K_INSERT = SCANCODE_TO_KEYCODE(SCANCODE_INSERT),
    K_HOME = SCANCODE_TO_KEYCODE(SCANCODE_HOME),
    K_PAGEUP = SCANCODE_TO_KEYCODE(SCANCODE_PAGEUP),
    K_DELETE = '\x7F',
    K_END = SCANCODE_TO_KEYCODE(SCANCODE_END),
    K_PAGEDOWN = SCANCODE_TO_KEYCODE(SCANCODE_PAGEDOWN),
    K_RIGHT = SCANCODE_TO_KEYCODE(SCANCODE_RIGHT),
    K_LEFT = SCANCODE_TO_KEYCODE(SCANCODE_LEFT),
    K_DOWN = SCANCODE_TO_KEYCODE(SCANCODE_DOWN),
    K_UP = SCANCODE_TO_KEYCODE(SCANCODE_UP),

    K_NUMLOCKCLEAR = SCANCODE_TO_KEYCODE(SCANCODE_NUMLOCKCLEAR),
    K_KP_DIVIDE = SCANCODE_TO_KEYCODE(SCANCODE_KP_DIVIDE),
    K_KP_MULTIPLY = SCANCODE_TO_KEYCODE(SCANCODE_KP_MULTIPLY),
    K_KP_MINUS = SCANCODE_TO_KEYCODE(SCANCODE_KP_MINUS),
    K_KP_PLUS = SCANCODE_TO_KEYCODE(SCANCODE_KP_PLUS),
    K_KP_ENTER = SCANCODE_TO_KEYCODE(SCANCODE_KP_ENTER),
    K_KP_1 = SCANCODE_TO_KEYCODE(SCANCODE_KP_1),
    K_KP_2 = SCANCODE_TO_KEYCODE(SCANCODE_KP_2),
    K_KP_3 = SCANCODE_TO_KEYCODE(SCANCODE_KP_3),
    K_KP_4 = SCANCODE_TO_KEYCODE(SCANCODE_KP_4),
    K_KP_5 = SCANCODE_TO_KEYCODE(SCANCODE_KP_5),
    K_KP_6 = SCANCODE_TO_KEYCODE(SCANCODE_KP_6),
    K_KP_7 = SCANCODE_TO_KEYCODE(SCANCODE_KP_7),
    K_KP_8 = SCANCODE_TO_KEYCODE(SCANCODE_KP_8),
    K_KP_9 = SCANCODE_TO_KEYCODE(SCANCODE_KP_9),
    K_KP_0 = SCANCODE_TO_KEYCODE(SCANCODE_KP_0),
    K_KP_PERIOD = SCANCODE_TO_KEYCODE(SCANCODE_KP_PERIOD),

    K_APPLICATION = SCANCODE_TO_KEYCODE(SCANCODE_APPLICATION),
    K_POWER = SCANCODE_TO_KEYCODE(SCANCODE_POWER),
    K_KP_EQUALS = SCANCODE_TO_KEYCODE(SCANCODE_KP_EQUALS),
    K_F13 = SCANCODE_TO_KEYCODE(SCANCODE_F13),
    K_F14 = SCANCODE_TO_KEYCODE(SCANCODE_F14),
    K_F15 = SCANCODE_TO_KEYCODE(SCANCODE_F15),
    K_F16 = SCANCODE_TO_KEYCODE(SCANCODE_F16),
    K_F17 = SCANCODE_TO_KEYCODE(SCANCODE_F17),
    K_F18 = SCANCODE_TO_KEYCODE(SCANCODE_F18),
    K_F19 = SCANCODE_TO_KEYCODE(SCANCODE_F19),
    K_F20 = SCANCODE_TO_KEYCODE(SCANCODE_F20),
    K_F21 = SCANCODE_TO_KEYCODE(SCANCODE_F21),
    K_F22 = SCANCODE_TO_KEYCODE(SCANCODE_F22),
    K_F23 = SCANCODE_TO_KEYCODE(SCANCODE_F23),
    K_F24 = SCANCODE_TO_KEYCODE(SCANCODE_F24),
    K_EXECUTE = SCANCODE_TO_KEYCODE(SCANCODE_EXECUTE),
    K_HELP = SCANCODE_TO_KEYCODE(SCANCODE_HELP),
    K_MENU = SCANCODE_TO_KEYCODE(SCANCODE_MENU),
    K_SELECT = SCANCODE_TO_KEYCODE(SCANCODE_SELECT),
    K_STOP = SCANCODE_TO_KEYCODE(SCANCODE_STOP),
    K_AGAIN = SCANCODE_TO_KEYCODE(SCANCODE_AGAIN),
    K_UNDO = SCANCODE_TO_KEYCODE(SCANCODE_UNDO),
    K_CUT = SCANCODE_TO_KEYCODE(SCANCODE_CUT),
    K_COPY = SCANCODE_TO_KEYCODE(SCANCODE_COPY),
    K_PASTE = SCANCODE_TO_KEYCODE(SCANCODE_PASTE),
    K_FIND = SCANCODE_TO_KEYCODE(SCANCODE_FIND),
    K_MUTE = SCANCODE_TO_KEYCODE(SCANCODE_MUTE),
    K_VOLUMEUP = SCANCODE_TO_KEYCODE(SCANCODE_VOLUMEUP),
    K_VOLUMEDOWN = SCANCODE_TO_KEYCODE(SCANCODE_VOLUMEDOWN),
    K_KP_COMMA = SCANCODE_TO_KEYCODE(SCANCODE_KP_COMMA),
    K_KP_EQUALSAS400 =
        SCANCODE_TO_KEYCODE(SCANCODE_KP_EQUALSAS400),

    K_ALTERASE = SCANCODE_TO_KEYCODE(SCANCODE_ALTERASE),
    K_SYSREQ = SCANCODE_TO_KEYCODE(SCANCODE_SYSREQ),
    K_CANCEL = SCANCODE_TO_KEYCODE(SCANCODE_CANCEL),
    K_CLEAR = SCANCODE_TO_KEYCODE(SCANCODE_CLEAR),
    K_PRIOR = SCANCODE_TO_KEYCODE(SCANCODE_PRIOR),
    K_RETURN2 = SCANCODE_TO_KEYCODE(SCANCODE_RETURN2),
    K_SEPARATOR = SCANCODE_TO_KEYCODE(SCANCODE_SEPARATOR),
    K_OUT = SCANCODE_TO_KEYCODE(SCANCODE_OUT),
    K_OPER = SCANCODE_TO_KEYCODE(SCANCODE_OPER),
    K_CLEARAGAIN = SCANCODE_TO_KEYCODE(SCANCODE_CLEARAGAIN),
    K_CRSEL = SCANCODE_TO_KEYCODE(SCANCODE_CRSEL),
    K_EXSEL = SCANCODE_TO_KEYCODE(SCANCODE_EXSEL),

    K_KP_00 = SCANCODE_TO_KEYCODE(SCANCODE_KP_00),
    K_KP_000 = SCANCODE_TO_KEYCODE(SCANCODE_KP_000),
    K_THOUSANDSSEPARATOR =
        SCANCODE_TO_KEYCODE(SCANCODE_THOUSANDSSEPARATOR),
    K_DECIMALSEPARATOR =
        SCANCODE_TO_KEYCODE(SCANCODE_DECIMALSEPARATOR),
    K_CURRENCYUNIT = SCANCODE_TO_KEYCODE(SCANCODE_CURRENCYUNIT),
    K_CURRENCYSUBUNIT =
        SCANCODE_TO_KEYCODE(SCANCODE_CURRENCYSUBUNIT),
    K_KP_LEFTPAREN = SCANCODE_TO_KEYCODE(SCANCODE_KP_LEFTPAREN),
    K_KP_RIGHTPAREN = SCANCODE_TO_KEYCODE(SCANCODE_KP_RIGHTPAREN),
    K_KP_LEFTBRACE = SCANCODE_TO_KEYCODE(SCANCODE_KP_LEFTBRACE),
    K_KP_RIGHTBRACE = SCANCODE_TO_KEYCODE(SCANCODE_KP_RIGHTBRACE),
    K_KP_TAB = SCANCODE_TO_KEYCODE(SCANCODE_KP_TAB),
    K_KP_BACKSPACE = SCANCODE_TO_KEYCODE(SCANCODE_KP_BACKSPACE),
    K_KP_A = SCANCODE_TO_KEYCODE(SCANCODE_KP_A),
    K_KP_B = SCANCODE_TO_KEYCODE(SCANCODE_KP_B),
    K_KP_C = SCANCODE_TO_KEYCODE(SCANCODE_KP_C),
    K_KP_D = SCANCODE_TO_KEYCODE(SCANCODE_KP_D),
    K_KP_E = SCANCODE_TO_KEYCODE(SCANCODE_KP_E),
    K_KP_F = SCANCODE_TO_KEYCODE(SCANCODE_KP_F),
    K_KP_XOR = SCANCODE_TO_KEYCODE(SCANCODE_KP_XOR),
    K_KP_POWER = SCANCODE_TO_KEYCODE(SCANCODE_KP_POWER),
    K_KP_PERCENT = SCANCODE_TO_KEYCODE(SCANCODE_KP_PERCENT),
    K_KP_LESS = SCANCODE_TO_KEYCODE(SCANCODE_KP_LESS),
    K_KP_GREATER = SCANCODE_TO_KEYCODE(SCANCODE_KP_GREATER),
    K_KP_AMPERSAND = SCANCODE_TO_KEYCODE(SCANCODE_KP_AMPERSAND),
    K_KP_DBLAMPERSAND =
        SCANCODE_TO_KEYCODE(SCANCODE_KP_DBLAMPERSAND),
    K_KP_VERTICALBAR =
        SCANCODE_TO_KEYCODE(SCANCODE_KP_VERTICALBAR),
    K_KP_DBLVERTICALBAR =
        SCANCODE_TO_KEYCODE(SCANCODE_KP_DBLVERTICALBAR),
    K_KP_COLON = SCANCODE_TO_KEYCODE(SCANCODE_KP_COLON),
    K_KP_HASH = SCANCODE_TO_KEYCODE(SCANCODE_KP_HASH),
    K_KP_SPACE = SCANCODE_TO_KEYCODE(SCANCODE_KP_SPACE),
    K_KP_AT = SCANCODE_TO_KEYCODE(SCANCODE_KP_AT),
    K_KP_EXCLAM = SCANCODE_TO_KEYCODE(SCANCODE_KP_EXCLAM),
    K_KP_MEMSTORE = SCANCODE_TO_KEYCODE(SCANCODE_KP_MEMSTORE),
    K_KP_MEMRECALL = SCANCODE_TO_KEYCODE(SCANCODE_KP_MEMRECALL),
    K_KP_MEMCLEAR = SCANCODE_TO_KEYCODE(SCANCODE_KP_MEMCLEAR),
    K_KP_MEMADD = SCANCODE_TO_KEYCODE(SCANCODE_KP_MEMADD),
    K_KP_MEMSUBTRACT =
        SCANCODE_TO_KEYCODE(SCANCODE_KP_MEMSUBTRACT),
    K_KP_MEMMULTIPLY =
        SCANCODE_TO_KEYCODE(SCANCODE_KP_MEMMULTIPLY),
    K_KP_MEMDIVIDE = SCANCODE_TO_KEYCODE(SCANCODE_KP_MEMDIVIDE),
    K_KP_PLUSMINUS = SCANCODE_TO_KEYCODE(SCANCODE_KP_PLUSMINUS),
    K_KP_CLEAR = SCANCODE_TO_KEYCODE(SCANCODE_KP_CLEAR),
    K_KP_CLEARENTRY = SCANCODE_TO_KEYCODE(SCANCODE_KP_CLEARENTRY),
    K_KP_BINARY = SCANCODE_TO_KEYCODE(SCANCODE_KP_BINARY),
    K_KP_OCTAL = SCANCODE_TO_KEYCODE(SCANCODE_KP_OCTAL),
    K_KP_DECIMAL = SCANCODE_TO_KEYCODE(SCANCODE_KP_DECIMAL),
    K_KP_HEXADECIMAL =
        SCANCODE_TO_KEYCODE(SCANCODE_KP_HEXADECIMAL),

    K_LCTRL = SCANCODE_TO_KEYCODE(SCANCODE_LCTRL),
    K_LSHIFT = SCANCODE_TO_KEYCODE(SCANCODE_LSHIFT),
    K_LALT = SCANCODE_TO_KEYCODE(SCANCODE_LALT),
    K_LGUI = SCANCODE_TO_KEYCODE(SCANCODE_LGUI),
    K_RCTRL = SCANCODE_TO_KEYCODE(SCANCODE_RCTRL),
    K_RSHIFT = SCANCODE_TO_KEYCODE(SCANCODE_RSHIFT),
    K_RALT = SCANCODE_TO_KEYCODE(SCANCODE_RALT),
    K_RGUI = SCANCODE_TO_KEYCODE(SCANCODE_RGUI),

    K_MODE = SCANCODE_TO_KEYCODE(SCANCODE_MODE),

    K_AUDIONEXT = SCANCODE_TO_KEYCODE(SCANCODE_AUDIONEXT),
    K_AUDIOPREV = SCANCODE_TO_KEYCODE(SCANCODE_AUDIOPREV),
    K_AUDIOSTOP = SCANCODE_TO_KEYCODE(SCANCODE_AUDIOSTOP),
    K_AUDIOPLAY = SCANCODE_TO_KEYCODE(SCANCODE_AUDIOPLAY),
    K_AUDIOMUTE = SCANCODE_TO_KEYCODE(SCANCODE_AUDIOMUTE),
    K_MEDIASELECT = SCANCODE_TO_KEYCODE(SCANCODE_MEDIASELECT),
    K_WWW = SCANCODE_TO_KEYCODE(SCANCODE_WWW),
    K_MAIL = SCANCODE_TO_KEYCODE(SCANCODE_MAIL),
    K_CALCULATOR = SCANCODE_TO_KEYCODE(SCANCODE_CALCULATOR),
    K_COMPUTER = SCANCODE_TO_KEYCODE(SCANCODE_COMPUTER),
    K_AC_SEARCH = SCANCODE_TO_KEYCODE(SCANCODE_AC_SEARCH),
    K_AC_HOME = SCANCODE_TO_KEYCODE(SCANCODE_AC_HOME),
    K_AC_BACK = SCANCODE_TO_KEYCODE(SCANCODE_AC_BACK),
    K_AC_FORWARD = SCANCODE_TO_KEYCODE(SCANCODE_AC_FORWARD),
    K_AC_STOP = SCANCODE_TO_KEYCODE(SCANCODE_AC_STOP),
    K_AC_REFRESH = SCANCODE_TO_KEYCODE(SCANCODE_AC_REFRESH),
    K_AC_BOOKMARKS = SCANCODE_TO_KEYCODE(SCANCODE_AC_BOOKMARKS),

    K_BRIGHTNESSDOWN =
        SCANCODE_TO_KEYCODE(SCANCODE_BRIGHTNESSDOWN),
    K_BRIGHTNESSUP = SCANCODE_TO_KEYCODE(SCANCODE_BRIGHTNESSUP),
    K_DISPLAYSWITCH = SCANCODE_TO_KEYCODE(SCANCODE_DISPLAYSWITCH),
    K_KBDILLUMTOGGLE =
        SCANCODE_TO_KEYCODE(SCANCODE_KBDILLUMTOGGLE),
    K_KBDILLUMDOWN = SCANCODE_TO_KEYCODE(SCANCODE_KBDILLUMDOWN),
    K_KBDILLUMUP = SCANCODE_TO_KEYCODE(SCANCODE_KBDILLUMUP),
    K_EJECT = SCANCODE_TO_KEYCODE(SCANCODE_EJECT),
    K_SLEEP = SCANCODE_TO_KEYCODE(SCANCODE_SLEEP),
    K_APP1 = SCANCODE_TO_KEYCODE(SCANCODE_APP1),
    K_APP2 = SCANCODE_TO_KEYCODE(SCANCODE_APP2),

    K_AUDIOREWIND = SCANCODE_TO_KEYCODE(SCANCODE_AUDIOREWIND),
    K_AUDIOFASTFORWARD = SCANCODE_TO_KEYCODE(SCANCODE_AUDIOFASTFORWARD),

    K_SOFTLEFT = SCANCODE_TO_KEYCODE(SCANCODE_SOFTLEFT),
    K_SOFTRIGHT = SCANCODE_TO_KEYCODE(SCANCODE_SOFTRIGHT),
    K_CALL = SCANCODE_TO_KEYCODE(SCANCODE_CALL),
    K_ENDCALL = SCANCODE_TO_KEYCODE(SCANCODE_ENDCALL)
};

enum Keymod
{
    MODK_NONE = 0x0000,
    MODK_LSHIFT = 0x0001,
    MODK_RSHIFT = 0x0002,
    MODK_LCTRL = 0x0040,
    MODK_RCTRL = 0x0080,
    MODK_LALT = 0x0100,
    MODK_RALT = 0x0200,
    MODK_LGUI = 0x0400,
    MODK_RGUI = 0x0800,
    MODK_NUM = 0x1000,
    MODK_CAPS = 0x2000,
    MODK_MODE = 0x4000,
    MODK_SCROLL = 0x8000,

    MOD_CTRL = MODK_LCTRL | MODK_RCTRL,
    MODK_SHIFT = MODK_LSHIFT | MODK_RSHIFT,
    // MODK_ALT = 768,
    MODK_ALT = MODK_LALT | MODK_RALT,
    MODK_GUI = MODK_LGUI | MODK_RGUI,

    MODK_RESERVED = MODK_SCROLL 
};

struct Keysym
{
    Scancode scancode;
    Keycode sym;
    Keymod mode;
};


#endif