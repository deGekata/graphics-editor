#include "EventManager.hpp"


bool EventManager::processEvent(Event* event) {
    if (!processChildrenEvent(event)) {
        return processSelfEvent(event);
    } else {
        return true;
    }
    return false;
}

bool  EventManager::processSelfEvent(Event* event) {
    return false;
}

bool  EventManager::processChildrenEvent(Event* event) {
    myAssert(event == NULL, "event must not be NULL");
    switch(event->type) {
        case EventType::KEYDOWN:{
            break;
        }

        case EventType::KEYUP:{
            break;
        }

        // case EventType::MOUSEMOTION:{
        //     break;
        // }

        // case EventType::MOUSE_ENTER:{
        //     break;
        // }

        // case EventType::MOUSE_LEAVE:{
        //     break;
        // }
        
        case EventType::MOUSEBUTTONDOWN:{
            break;
        }

        case EventType::MOUSEBUTTONUP:{
            break;
        }




        default:
            myAssert(false, "unknown event");
            break;
    }

    return false;
}


Widget* EventManager::mapWidgetFromPos(Point pos) {
    // std::cout << "mapping\n";
    static int cnt = 0;
    // std::cout << cnt;
    if (this->objective_->constraints_.inRect(pos)) {
        for (auto child: this->objective_->items) {
            cnt++;
            Widget* mp = child->event_manager->mapWidgetFromPos(child->mapFromParent(pos));
            cnt--;
            if (mp != NULL) {
                // std::cout << "NOT NUUUL\n";
                return mp;
            }
        }
        return this->objective_;
    }
    // std::cout << "always null";
    return NULL;
}
