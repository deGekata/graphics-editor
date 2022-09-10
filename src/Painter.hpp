#ifndef PAINTER_HPP
#define PAINTER_HPP

#include "Utilities.hpp"

class Painter {
    void repaint();

    void drawLine(Point p1, Point p2);

    void drawLine(int x1, int y1, int x2, int y2) { 
        drawLine(Point(x1, y1), Point(x2, y2)); 
    }

    
    void drawPoint(Point p1);
    void drawPoint(int x, int y) {
        drawPoint(Point(x, y));
    }
};



#endif