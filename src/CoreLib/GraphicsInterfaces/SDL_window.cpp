#include "SDL_window.hpp"

#include "Window.hpp"


Window::Window(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0) {
    rsp_ = new Window_(width, height, x, y, flags);
}



Window::~Window() {
        printf("dtooooooooooooor-----------");

    // delete rsp_;
}

int Window::startGraphicalLib() {
    return Window_::startGraphicalLib();
}

void Window::stopGraphicalLib() {
    return Window_::stopGraphicalLib();
}


