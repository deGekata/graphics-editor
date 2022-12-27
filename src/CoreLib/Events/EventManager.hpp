#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "Utilities/Logger.hpp"
#include "Widgets/Widget.hpp"
#include "Events/Event.hpp"

// class WindowEventManager;
class Widget;

struct WidgetCoords {
    Widget* widget;
    Point   pos;
};

class EventManager {
protected:
    Widget* objective_;
    EventManager() {}
    EventManager(Widget* objective) {
        // UNUSED(objective);
        myAssert(objective == NULL, "must not be equal to NULL");
        objective_ = objective;
    }

public:
    virtual bool processChildrenEvent(Event* event);
    virtual bool processEvent        (Event* event);

    virtual WidgetCoords mapChildWidgetFromPos(Point pos);
    virtual WidgetCoords mapWidgetFromPos(Point pos);
    virtual WidgetCoords mapChildWidgetUnmodifiedFromPos(Point pos);
    int mapEnterLeaveEvents(Event* event);
    int mapChildEnterLeaveEvents(Event* event);
    int resolveEnterLeaveEvents(Event* event, WidgetCoords before, WidgetCoords after);
    friend class Widget;
    // TODO:
};


#endif
