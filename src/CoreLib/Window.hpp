#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <inttypes.h>

class Window_;

class Window {
private:
    Window_* rsp_;
public:
    Window(int width, int height, int x, int y, uint32_t flags);

    ~Window();

    static int startGraphicalLib();

    static void stopGraphicalLib();

    virtual void exec() {}
    friend class Painter;
};


#endif