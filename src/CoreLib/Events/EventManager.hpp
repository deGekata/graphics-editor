#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "Utilities/Logger.hpp"
#include "Widgets/Widget.hpp"
#include "Events/Event.hpp"

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
    virtual bool processChildrenEvent(Event* event);
    virtual bool processSelfEvent    (Event* event);
    virtual bool processEvent        (Event* event);

    Widget* mapWidgetFromPos(Point pos);
    friend class Widget;
    // TODO:
};
#endif
