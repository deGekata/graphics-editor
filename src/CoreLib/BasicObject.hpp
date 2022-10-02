#ifndef BASIC_OBJECT_HPP
#define BASIC_OBJECT_HPP


#include "Event.hpp"
#include "Painter.hpp"


class BasicObject {
public: 
    virtual void event(Event& cur_event) {};
    // virtual int  paint(Painter* painter) { return 0;};
    // some slots functionality
    
    
};


#endif