#include <iostream> 
#include "MyWindow.hpp"

int main(__attribute__((unused)) int argv, __attribute__((unused)) char** args) {

    Window::startGraphicalLib();

    MyWindow window;
    Painter painter(window);
    window.setPainter(&painter);
    window.exec();
    

    Window::stopGraphicalLib();
    SDL_Quit();
    
    
    // itm_child.parent_base_point = {0, 0};
    // itm_child.rotation_angle_ = -1 * M_PI;
    // std::cout << itm_child.mapOnParent({1, 2}) << " fs\n";
    return 0;
}

