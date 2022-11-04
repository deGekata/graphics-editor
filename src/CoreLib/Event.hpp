#ifndef EVENT_HPP
#define EVENT_HPP
#include "SDL.h"

class Event_;

class Event {
private:
    Event_* rsp_ = NULL;
public:
    void accept() {
        is_processed_ = true;
    }
    
    SDL_Event event;
    
    bool is_processed_ = false;

    // static void connect()
};

#endif