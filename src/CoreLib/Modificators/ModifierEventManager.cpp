#include "ModifierEventManager.hpp"
#include "WidgetModifier.hpp"

bool ModifierEventManager::processEvent(Event* event) {
    // std::cout << "ModifierEventManager::processEvent" << std::endl;
    objective_->processSelfEvent(event);
    
    /*switch(event->type) {
        case EventType::KEYDOWN:{
            break;
        }

        case EventType::KEYUP:{
            break;
        }


        case EventType::MOUSE_ENTER:{
            break;
        }

        case EventType::MOUSE_LEAVE:{
            break;
        }
        
        case EventType::MOUSEMOTION:{
            if ()
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
    }*/
    
    Event temp_event = *event;
    if (!processChildrenEvent(&temp_event)) {
        return processTargetOrModifier(&temp_event);   

    } else {
        return true;
    }
    return false;
}

bool ModifierEventManager::processTargetOrModifier(Event* event) {
    Point pos;
    Event& temp_event = *event;
    if (temp_event.type == EventType::MOUSEMOTION) {
        pos = temp_event.mouse_motion.pos;
    } else if (temp_event.type == EventType::MOUSEBUTTONDOWN || temp_event.type == EventType::MOUSEBUTTONUP) {
        pos = temp_event.mouse_button.pos;
    } else {
        return false;
    }

    //modify for local coordinates
    if (((WidgetModifier*)this->objective_)->child_mod_ == nullptr) {
        pos = pos - ((WidgetModifier*)this->objective_)->target_widget_->pos_;
        
        //check for motion event
        if (!((WidgetModifier*)this->objective_)->target_widget_->constraints_.inRect(pos)) {
            //check for leave event
            if (temp_event.type == EventType::MOUSEMOTION &&
                ((WidgetModifier*)this->objective_)->target_widget_->constraints_.inRect(pos - temp_event.mouse_motion.rel_pos)) 
            {
                temp_event.type = EventType::MOUSE_LEAVE;
                ((WidgetModifier*)this->objective_)->target_widget_->event_manager->processEvent(&temp_event);
                temp_event.type = EventType::MOUSEMOTION;
            }
            return false;
        }
    } else {
        pos = ((WidgetModifier*)this->objective_)->child_mod_->mapFromParentModifier(pos);
        
        //check for motion event
        if (!(((WidgetModifier*)this->objective_)->child_mod_->constraints_.inRect(pos))) {
            //check for leave event
            if (temp_event.type == EventType::MOUSEMOTION &&
                ((WidgetModifier*)this->objective_)->child_mod_->constraints_.inRect(pos - temp_event.mouse_motion.rel_pos)) 
            {
                temp_event.type = EventType::MOUSE_LEAVE;
                ((WidgetModifier*)this->objective_)->child_mod_->event_manager->processEvent(&temp_event);
                temp_event.type = EventType::MOUSEMOTION;
            }
            return false;
        }
    }

    if (temp_event.type == EventType::MOUSEMOTION) {
        temp_event.mouse_motion.pos = pos;
    } else if (temp_event.type == EventType::MOUSEBUTTONDOWN || temp_event.type == EventType::MOUSEBUTTONUP) {
        temp_event.mouse_button.pos = pos;
    }
    

    //possibly send enter event and send mousemotion event
    if (((WidgetModifier*)this->objective_)->child_mod_ == nullptr) {
        if (temp_event.type == EventType::MOUSEMOTION &&
            !((WidgetModifier*)this->objective_)->target_widget_->constraints_.inRect(pos - temp_event.mouse_motion.rel_pos)) 
        {
            temp_event.type = EventType::MOUSE_ENTER;
            ((WidgetModifier*)this->objective_)->target_widget_->event_manager->processEvent(&temp_event);
            temp_event.type = EventType::MOUSEMOTION;
        }
        return ((WidgetModifier*)this->objective_)->target_widget_->event_manager->processEvent(&temp_event);
    } else {
        if (temp_event.type == EventType::MOUSEMOTION &&
            !((WidgetModifier*)this->objective_)->child_mod_->constraints_.inRect(pos - temp_event.mouse_motion.rel_pos)) 
        {
            temp_event.type = EventType::MOUSE_ENTER;
            ((WidgetModifier*)this->objective_)->child_mod_->event_manager->processEvent(&temp_event);
            temp_event.type = EventType::MOUSEMOTION;
        }
        return ((WidgetModifier*)this->objective_)->child_mod_->event_manager->processEvent(&temp_event);
    } 
}


bool  ModifierEventManager::processChildrenEvent(Event* event) {
    //TODO:
    myAssert(event == NULL, "event must not be NULL");
    switch(event->type) {
        case EventType::KEYDOWN:{
            break;
        }

        case EventType::KEYUP:{
            break;
        }

        case EventType::MOUSEMOTION:{
            Event n_event = *event;
            WidgetCoords after = mapChildWidgetFromPos(event->mouse_motion.pos);
            WidgetCoords before = mapChildWidgetFromPos(event->mouse_motion.pos - event->mouse_motion.rel_pos);
            
            MouseMotionType n_motion_type = event->mouse_motion_type;
            switch (event->mouse_motion_type) {
                case MouseMotionType::FULL:{
                    bool process_enter = true;
                    bool process_leave = true;
                    if (before.widget != after.widget && before.widget != NULL) {
                        n_event.type = EventType::MOUSE_LEAVE;
                        before.widget->event_manager->processEvent(&n_event);
                        process_leave = false;
                    }

                    if (before.widget != after.widget && after.widget != NULL) {
                        n_event.type = EventType::MOUSE_ENTER;
                        after.widget->event_manager->processEvent(&n_event);
                        n_event.type = EventType::MOUSEMOTION;
                        after.widget->event_manager->processEvent(&n_event);
                        process_enter = false;
                    }

                    if (!process_enter && !process_leave) {
                        return true;
                    } else if (!process_enter && process_leave) {
                        n_motion_type = MouseMotionType::ONLY_LEAVE;

                    } else if (process_enter && !process_leave) {
                        n_motion_type = MouseMotionType::ONLY_ENTER;

                    } else if (process_enter && process_leave) {
                        n_motion_type = MouseMotionType::FULL;
                    }

                    // std::cout << "FULL" << std::endl;
                    break;
                }

                case MouseMotionType::ONLY_ENTER:{
                    if (before.widget != after.widget && after.widget != NULL) {
                        n_event.type = EventType::MOUSE_ENTER;
                        after.widget->event_manager->processEvent(&n_event);
                        n_event.type = EventType::MOUSEMOTION;
                        after.widget->event_manager->processEvent(&n_event);
                        return true;
                    }
                    n_motion_type = MouseMotionType::ONLY_ENTER;
                    std::cout << "ENTER" << std::endl;
                    break;
                }
                
                case MouseMotionType::ONLY_LEAVE:{
                    if (before.widget != after.widget && before.widget != NULL) {
                        n_event.type = EventType::MOUSE_LEAVE;
                        before.widget->event_manager->processEvent(&n_event);
                        return true;
                    }
                    n_motion_type = MouseMotionType::ONLY_LEAVE;
                    std::cout << "LEAVE" << std::endl;
                    break;
                }
                
                default:
                    myAssert(false, "MouseMotionType");
                    break;

            }

            event->mouse_motion_type = n_motion_type;
            return false;
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


// WidgetCoords ModifierEventManager::mapChildWidgetFromPos(Point pos) {
//     //check for modifiers
//     //probably no modifiers))))
//     if (this->objective_->modifier_list_->cnt != 0) 
//     {   
//         if (!this->objective_->modifier_list_->top->constraints_.inRect(objective_->modifier_list_->top->mapFromParentModifier(pos)))
//             return NULL;
//         // std::cout << "modddd " << objective_->modifier_list_->top->rect_.point_ << ":point  size:" << objective_->modifier_list_->top->rect_.size_ << "\n";
//         // std::cout << "modddd pos  " << objective_->modifier_list_->top->pos_ << "\n";
//         // std::cout << "modddd pos calc  " << pos << "\n";
//         return this->objective_->modifier_list_->top->event_manager->mapWidgetFromPos(objective_->modifier_list_->top->mapFromParentModifier(pos));
//     }

//     pos = ((WidgetModifier*)this->objective_)->mapFromParentModifier(pos);
//     if (this->objective_->constraints_.inRect(pos)) {
//         for (auto child: this->objective_->items) {

//             Widget* mp = child->event_manager->mapChildWidgetFromPos(child->mapFromParent(pos));

//             if (mp != NULL) {
//                 // std::cout << "NOT NUUUL\n";
//                 return mp;
//             }
//         }
        
//         return this->objective_;

//     }

//     // std::cout << "always null";
//     return NULL;
// }
  