#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "Logger.hpp"
#include "Widget.hpp"
#include "Event.hpp"

// class WindowEventManager;
class Widget;

class EventManager {
private:
    // WindowEventManager* dispatcher;
    Widget* objective_;
    EventManager(Widget* objective) {
        // UNUSED(objective);
        myAssert(objective == NULL, "must not be equal to NULL");
        objective_ = objective;
    }

public:
    bool processChildren(Event* event) {
        myAssert(event == NULL, "event must not be NULL");
        switch(event->type) {
            case EventType::MOUSEMOTION:{
                break;
            }
            
            case EventType::MOUSEBUTTONDOWN:{
                break;
            }

            case EventType::MOUSEBUTTONUP:{
                break;
            }

            // case :{
            //     break;
            // }

            // case :{
            //     break;
            // }


            default:
                myAssert(false, "unknown event");
                break;
        }
    }
    bool processParent(Event* event);
    Widget* mapPointPos(Point pos);
    friend class Widget;
    // TODO:
};
#endif