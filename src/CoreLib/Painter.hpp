#ifndef PAINTER_HPP
#define PAINTER_HPP

#include "Utilities.hpp"
// #include "SDL.h"
#include "Window.hpp"
// #include "Widget.hpp"
#include "Surface.hpp"
#include "Logger.hpp"



class Painter_;
class Widget;
class Window;

class Painter {
private:
public:
    Painter_* rsp_ = NULL;
    Surface* window_surface_ = NULL;
    Rect     window_rect_    = {};
public:
    Painter(Window* window);

    ~Painter();

    void setWindow(Window* window);

    int begin(Surface* surface);

    int end();

    int fillWindow();

    int setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    int setColor(const ColorF& color);

    void present();

    void repaint();

    int drawArrow(const PointF& p1, const PointF& p2);

    int drawLine(PointF p1, PointF p2);

    int drawLine(int x1, int y1, int x2, int y2);
    
    int drawPoint(PointF p1);

    int drawPoint(int x, int y);

    int drawPointBounded(int x, int y);
    

};



#endif