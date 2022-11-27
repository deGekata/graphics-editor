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
    bool processChildren(Event* event);
    bool processParent(Event* event);
    Widget* mapWidgetFromPos(Point pos);
    friend class Widget;
    // TODO:
};
#endif