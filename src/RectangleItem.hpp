#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "GraphicsGeometryItem.hpp"


class GraphicsRectangleItem : public GraphicsGeometryItem {
public:
    GraphicsRectangleItem(GraphicsItem* parent = NULL) : GraphicsGeometryItem(parent) {};
    GraphicsRectangleItem(Rect rect, Point point);

    GraphicsRectangleItem(const Point& pos) {
        rel_pos_.x_ = pos.x_;
        rel_pos_.y_ = pos.y_;
        // parent_base_point = pos;
    }

    int paint(Painter* painter) {
        if (painter == NULL) return 1;
        // Point absolute_pos = absPos(pos_);
        Transformation abs_transform = absTransformToParent();
        // std::cout << abs_transform << "\n";
        Point to_right = {100, 0};
        Point to_top = {0, 100};
        painter->drawLine(abs_transform * (rel_pos_ + to_right + to_top), abs_transform * (rel_pos_ + to_right - to_top));
        painter->drawLine(abs_transform * (rel_pos_ + to_right + to_top), abs_transform * (rel_pos_ - to_right + to_top));
        painter->drawLine(abs_transform * (rel_pos_ - to_right + to_top), abs_transform * (rel_pos_ - to_right - to_top));
        painter->drawLine(abs_transform * (rel_pos_ - to_right - to_top), abs_transform * (rel_pos_ + to_right - to_top));
        return 0;
    }
    ~GraphicsRectangleItem() {}
};


#endif