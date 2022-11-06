#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "Logger.hpp"
#include "Widget.hpp"
#include "Event.hpp"

class WindowEventManager;

class EventManager {
private:
    WindowEventManager* dispatcher;
    Widget* objective_;
    EventManager(Widget* objective) {
        // if (objective == NULL) {
        //     printError("objective must not be NULL");
        //     throw;
        // }
        // objective_ = objective;
        // std::cout << "manager_created!!!!";
        // exit(-1);
    }
public:
    bool processChildren(Event* event);
    bool processParent(Event* event);
    Widget* mapPointPos(Point pos);
    friend class Widget;
    // TODO:
};
#endif