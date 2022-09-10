#ifndef GRAPHICS_ITEM_HPP
#define GRAPHICS_ITEM_HPP

#include "Utilities.hpp"

class Painter;


class GraphicsItem {
public:
    GraphicsItem() = default;
    virtual ~GraphicsItem() = 0;
    virtual void paint(Painter* painter) = 0;
    virtual void pos()  = 0;
    
    const Rect& getRect() const { return rect_; };

    Point mapOnParent(const Point& point) {
        return parent_base_point + Point(point  .x_ / scale_x_, point.y_ / scale_y_).rotate(-rotation_angle_);
    }
    Rect rect_ = {0, 0};
    
    Point parent_base_point = {0, 0};
    GraphicsItem* parent = nullptr;
    double scale_x_ = 1.0, scale_y_ = 1.0;
    double rotation_angle_ = 0;
};


#endif