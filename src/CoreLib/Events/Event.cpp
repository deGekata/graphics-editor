#include "Event.hpp"




bool is_for_text_input(int sym) {
    return isprint(sym) || sym == Keycode::K_DELETE || sym == Keycode::K_ESCAPE;
}