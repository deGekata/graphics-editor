#include "SDL_window.hpp"

#include "Core/Window.hpp"
#include "Core/App.hpp"

Window::Window(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0) 
    :
    rect_({0, 0, width, height})
{
    central_widget_ = new Widget(rect_, Point(0, 0), nullptr);
    current_active_widget_ = central_widget_;
    rsp_ = new Window_(width, height, x, y, flags);
    id = rsp_->getWindowId();
    surface_ = new Surface(new Surface_(rsp_->window_surface));
    rect_ = {0, 0, width, height};
    
}

void Window::present() {
    this->central_widget_->buff_surface_.blitToOther(NULL, this->surface_, NULL);
    rsp_->updateWindowSurface();
    return;
}

void Window::processEvents() {
    Event event;
    while (this->manager_->pollEvent(&event, 0) > 0) {
        switch (event.type) {
            case EventType::MOUSEMOTION: {
                Widget* before, *after;
                after = current_active_widget_->event_manager->mapWidgetFromPos(event.mouse_motion.pos);
                before  = current_active_widget_->event_manager->mapWidgetFromPos(event.mouse_motion.pos - event.mouse_motion.rel_pos);
                if (before != NULL)
                    before->mouseMoveEvent(&event);

                if (before != after) {
                    std::cout << "leave_enter\n";
                    if (before != NULL) 
                        before->mouseLeaveEvent(&event);
                    if (after != NULL) 
                        after->mouseEnterEvent(&event);
                }
                //TODO:
                //some additional code for always tracking widgets
            }
            break;

            case EventType::MOUSEBUTTONUP  : {
                Widget* widg;
                widg = current_active_widget_->event_manager->mapWidgetFromPos(event.mouse_button.pos);
        
                if (widg != NULL) {
                    widg->mouseReleaseEvent(&event);
                }
                //TODO:
                //some additional code for always tracking widgets
            }
            break;

            case EventType::MOUSEBUTTONDOWN: {
                Widget* widg;
                widg = current_active_widget_->event_manager->mapWidgetFromPos(event.mouse_button.pos);
        
                if (widg != NULL) {
                    widg->mousePressEvent(&event);
                }
                //TODO:
                //some additional code for always tracking widgets
            }
            break;

            case EventType::KEYDOWN: {
                if (
                    this->current_text_input != NULL && 
                    is_for_text_input(event.keyboard.key.sym) &&
                    event.keyboard.key.mode == Keymod::MODK_NONE
                    ) 
                {
                    this->current_text_input->keyPressEvent(&event);
                } else {
                    this->current_active_widget_->event_manager->processEvent(&event);
                }
                break;
            }

            case EventType::KEYUP: {
                if (
                    this->current_text_input != NULL && 
                    is_for_text_input(event.keyboard.key.sym) &&
                    event.keyboard.key.mode == Keymod::MODK_NONE
                    ) 
                {
                    this->current_text_input->keyReleaseEvent(&event);
                } else {
                    this->current_active_widget_->event_manager->processEvent(&event);
                }
                break;
            }

            case EventType::MOUSEWHEEL: {
                std::cout << "unsupported event type, bruh\n";
                break;
            }
            
        default:
            break;
        }
    }
}




Window::~Window() {
    printf("dtooooooooooooor-----------");

    delete rsp_;
}




