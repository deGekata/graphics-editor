#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <inttypes.h>
#include "Surface.hpp"
#include "Widgets/Widget.hpp"
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
    Widget* central_widget_        = NULL;
    Widget* current_text_input     = NULL;
    Widget* current_active_widget_ = NULL;
    Window(int width, int height, int x, int y, uint32_t flags);

    ~Window();
    void present();
    virtual void update()        {}
    virtual void exec()          {}
    virtual void exec_() final   {}
    virtual void processEvents();

    friend class Painter;
    friend class App;
};


#endif