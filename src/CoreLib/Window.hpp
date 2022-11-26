#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <inttypes.h>
#include "Surface.hpp"
#include "Widget.hpp"
#include "App.hpp"

class Window_;
class Widget;
class App;

class Window {
protected:
    App* manager_;
public:
    Window_* rsp_ = NULL;
    Surface* surface_ = NULL;
    Rect rect_ = {};
    uint32_t id = 0;
public:
    Widget* central_widget_;
    Window(int width, int height, int x, int y, uint32_t flags);

    ~Window();
    void present();
    static int startGraphicalLib();

    static void stopGraphicalLib();

    virtual void exec() {}
    virtual void exec_() final {}

    friend class Painter;
    friend class App;
};


#endif