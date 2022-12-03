#include <iostream> 
#include "CustomClasses/MyWindow.hpp"
#include <assert.h>
// #include "CoreLib/GraphicsInterfaces/SDL_painter.hpp"
#include "thread"
#include "CoreLib/Core/App.hpp"


int main(__attribute__((unused)) int argv, __attribute__((unused)) char** args) {
    // Window::startGraphicalLib();
    int abc[] = {1, 4, 5, 8};
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

