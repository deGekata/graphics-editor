#include <iostream> 
#include "MyWindow.hpp"
#include <assert.h>
int main(__attribute__((unused)) int argv, __attribute__((unused)) char** args) {
    std::cout << triangleArea(Vector3D(20, 0, 0), Vector3D(0, 0, 30)) << "check";
    Window::startGraphicalLib();
    MyWindow window;
    Painter painter(window);
    window.setPainter(&painter);
    window.exec();
    

    Window::stopGraphicalLib();
    SDL_Quit();
    

    std::cout << "----\n";

    // Sphere sp(Vector3D(0, 0, 0), 10);
    // Ray vec(Vector3D(0., 5., 0.),  Vector3D(0, 5, 0));
    // std::cout << sp.intersect(vec);
    // itm_child.parent_base_point = {0, 0};
    // itm_child.rotation_angle_ = -1 * M_PI;
    // std::cout << itm_child.mapOnParent({1, 2}) << " fs\n";
    return 0;
}

