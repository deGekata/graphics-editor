#ifndef EVENT_HPP
#define EVENT_HPP
#include "..\..\SDL2\include\SDL2\SDL.h"

class Event {
    void accept() {
        is_processed_ = true;
    }

    

    SDL_Event event;
    
    bool is_processed_ = false;

    // static void connect()

};

#endif