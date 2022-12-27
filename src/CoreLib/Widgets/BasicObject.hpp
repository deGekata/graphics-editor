#ifndef BASIC_OBJECT_HPP
#define BASIC_OBJECT_HPP


#include "Event.hpp"
#include "Painter.hpp"


class BasicObject {
public: 
    virtual void event(Event* cur_event) { UNUSED(cur_event); }; //FIX:
    
};


#endif