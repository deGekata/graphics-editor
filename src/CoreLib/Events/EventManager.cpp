#include "EventManager.hpp"
#include "WidgetModifier.hpp"

bool EventManager::processEvent(Event* event) {
    if (!processChildrenEvent(event)) {
        return objective_->processSelfEvent(event);
    } else {
        return true;
    }
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

        case EventType::MOUSEMOTION:{
            return mapChildEnterLeaveEvents(event);
            break;
        }

        case EventType::MOUSE_ENTER:{ 
            break;
        }

        case EventType::MOUSE_LEAVE:{
            break;
        }
        
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

// maps widget by position from children of current widget
// input: pos - position in (possibly) modifier coordinates
WidgetCoords EventManager::mapChildWidgetFromPos(Point pos) {
    // this->objective_->mapFromParent()
    if (this->objective_->modifier_list_->cnt != 0) {   
        pos = objective_->mapProcessModifiers(pos);
    }

    if (this->objective_->constraints_.inRect(pos)) {
        for (auto child: this->objective_->items) {

            WidgetCoords mp = child->event_manager->mapWidgetFromPos(pos);
            if (mp.widget != NULL) {
                return mp;
            }
        }

        // return {this->objective_, pos};
    }

    return {NULL, Point{0, 0}};
}

WidgetCoords EventManager::mapWidgetFromPos(Point pos) {
    if (this->objective_->modifier_list_->cnt != 0) {

        if (!this->objective_->modifier_list_->top->constraints_.inRect(objective_->modifier_list_->top->mapFromParentModifier(pos)))
            return {NULL, Point{0, 0}};
        // std::cout << "modddd " << objective_->modifier_list_->top->rect_.point_ << ":point  size:" << objective_->modifier_list_->top->rect_.size_ << "\n";
        // std::cout << "modddd pos  " << objective_->modifier_list_->top->pos_ << "\n";
        // std::cout << "modddd pos calc  " << pos << "\n";
        return WidgetCoords{this->objective_->modifier_list_->top, 
                            objective_->modifier_list_->top->mapFromParentModifier(pos)};
        // return this->objective_->modifier_list_->top->event_manager->mapWidgetFromPos(objective_->modifier_list_->top->mapFromParentModifier(pos));
    }

    pos = objective_->mapFromParent(pos);
    if (this->objective_->constraints_.inRect(pos)) {
        WidgetCoords mp = mapChildWidgetUnmodifiedFromPos(pos);
        if (mp.widget != NULL) {
            return mp;
        }
        return {this->objective_, pos};
    }
    // std::cout << "always null";
    return {NULL, Point{0, 0}};
}

// maps child widget from unmodified local coordinates
WidgetCoords EventManager::mapChildWidgetUnmodifiedFromPos(Point pos) {
    if (this->objective_->constraints_.inRect(pos)) {
        for (auto child: this->objective_->items) {

            WidgetCoords mp = child->event_manager->mapWidgetFromPos(pos);
            if (mp.widget != NULL) {
                return mp;
            }
            
        }
    }

    return {NULL, Point{0, 0}};
}

int EventManager::mapChildEnterLeaveEvents(Event* event) {
    // std::cout << "mapEnterLeaveEvents\n";
    WidgetCoords before, after;
    after = objective_->event_manager->mapChildWidgetFromPos(event->mouse_motion.pos);
    before  = objective_->event_manager->mapChildWidgetFromPos(event->mouse_motion.pos - event->mouse_motion.rel_pos);
    return resolveEnterLeaveEvents(event, before, after);
}

int EventManager::mapEnterLeaveEvents(Event* event) {
    // std::cout << "mapEnterLeaveEvents\n";
    WidgetCoords before, after;
    after = objective_->event_manager->mapWidgetFromPos(event->mouse_motion.pos);
    before  = objective_->event_manager->mapWidgetFromPos(event->mouse_motion.pos - event->mouse_motion.rel_pos);
    return resolveEnterLeaveEvents(event, before, after);
}

int EventManager::resolveEnterLeaveEvents(Event* event, WidgetCoords before, WidgetCoords after) {
    int status = 0;
    if (before.widget != after.widget) {
        std::cout << "leave_enter\n";
        // if (before.widget != NULL && objective_->rect_.inRect(event->mouse_motion.pos - event->mouse_motion.rel_pos)) { 
        if (before.widget != NULL) { 
            status++;
            Event n_event = *event;
            n_event.mouse_motion.pos = before.pos;
            n_event.type = EventType::MOUSE_LEAVE;
            // before.widget->mouseLeaveEvent(&n_event);
            before.widget->event_manager->processEvent(&n_event);
        }
        
        if (after.widget != NULL) {
            status++;
            Event n_event = *event;
            n_event.mouse_motion.pos = after.pos;
            n_event.type = EventType::MOUSE_ENTER;
            // after.widget->mouseEnterEvent(&n_event);
            after.widget->event_manager->processEvent(&n_event);
        }
    }

    if (after.widget != NULL) {
        status = true;
        Event n_event = *event;
        n_event.mouse_motion.pos = after.pos;
        after.widget->event_manager->processEvent(&n_event);
    }
    //FIXME:
    
    return status;
}
