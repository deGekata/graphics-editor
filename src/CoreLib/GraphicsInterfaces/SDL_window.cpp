#include "SDL_window.hpp"

#include "Window.hpp"
#include "App.hpp"

Window::Window(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0) 
    :
    rect_({0, 0, width, height})
{
    central_widget_ = new Widget(rect_, Point(0, 0), nullptr);
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




Window::~Window() {
    printf("dtooooooooooooor-----------");

    delete rsp_;
}




