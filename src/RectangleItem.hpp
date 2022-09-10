#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "GraphicsGeometryItem.hpp"


class GraphicsRectangleItem : public GraphicsGeometryItem {
    GraphicsRectangleItem(GraphicsItem* parent = nullptr) {};
    GraphicsRectangleItem(Rect rect, Point point);


    void paint(Painter& painter) {
        
    }


    ~GraphicsRectangleItem() {}
};


#endif