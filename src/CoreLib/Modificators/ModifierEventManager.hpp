#ifndef MODIFIER_EVENT_MANAGER_HPP
#define MODIFIER_EVENT_MANAGER_HPP

#include "EventManager.hpp"

class ModifierEventManager : public EventManager {
private:
    ModifierEventManager() {}
    ModifierEventManager(Widget* objective) : 
        EventManager(objective)
    {}


public:
    virtual bool processChildrenEvent(Event* event) override;
    // virtual bool processSelfEvent    (Event* event) override;
    virtual bool processEvent        (Event* event) override;
    virtual bool processTargetOrModifier(Event* event);
    // virtual WidgetCoords mapChildWidgetFromPos(Point pos) override;
    // virtual WidgetCoords mapWidgetFromPos(Point pos) override;
    // virtual WidgetCoords mapChildWidgetUnmodifiedFromPos(Point pos) override;
    friend class WidgetModifier;
};

#endif
