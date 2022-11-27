#include "EventManager.hpp"


bool  EventManager::processChildren(Event* event){
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


Widget* EventManager::mapWidgetFromPos(Point pos) {
    
}
