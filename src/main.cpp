#include <iostream> 
#include "MyWindow.hpp"
#include <assert.h>
#include "CoreLib/GraphicsInterfaces/SDL_painter.hpp"
#include "thread"
#include "App.hpp"


int main(__attribute__((unused)) int argv, __attribute__((unused)) char** args) {
    // Window::startGraphicalLib();
    MyWindow window(800, 800);
    Painter painter(&window);
    window.setPainter(&painter);
    painter.setWindow(&window);
    // window.exec();
    // // while(true) {
    App& instance = App::getInstance();
    // }
    instance.addWindow(&window);
    instance.exec();

    // Window::stopGraphicalLib();
    SDL_Quit();

    return 0;
}

