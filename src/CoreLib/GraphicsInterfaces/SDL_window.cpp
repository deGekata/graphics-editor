#include "SDL_window.hpp"

#include "Core/Window.hpp"
#include "Core/App.hpp"

Window::Window(int width = 800, int height = 600, int x = 1000, int y = 0, uint32_t flags = 0) 
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
                int status = current_active_widget_->event_manager->mapEnterLeaveEvents(&event);
                //TODO:
                //some additional code for always tracking widgets
            }
            break;

            case EventType::MOUSEBUTTONUP  : {
                WidgetCoords widg = current_active_widget_->event_manager->mapWidgetFromPos(event.mouse_button.pos);
        
                if (widg.widget != NULL) {
                    event.mouse_button.pos = widg.pos;
                    // widg.widget->mouseReleaseEvent(&event);
                    widg.widget->event_manager->processEvent(&event);
                }
                //TODO:
                //some additional code for always tracking widgets
            }
            break;

            case EventType::MOUSEBUTTONDOWN: {
                WidgetCoords widg = current_active_widget_->event_manager->mapWidgetFromPos(event.mouse_button.pos);
        
                if (widg.widget != NULL) {
                    event.mouse_button.pos = widg.pos;
                    // widg.widget-> mousePressEvent(&event);
                    widg.widget->event_manager->processEvent(&event);
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




