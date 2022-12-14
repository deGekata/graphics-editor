#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "CoreLib/Core/GraphicsGeometryItem.hpp"


class GraphicsRectangleItem : public GraphicsGeometryItem {
public:
    GraphicsRectangleItem(GraphicsItem* parent = NULL) : GraphicsGeometryItem(parent) {};
    GraphicsRectangleItem(RectF rect, PointF point);

    GraphicsRectangleItem(const PointF& pos) {
        rel_pos_.x_ = pos.x_;
        rel_pos_.y_ = pos.y_;
    }

    int paint(Painter* painter) {
        if (painter == NULL) return 1;
        Transformation abs_transform = absTransformToParent();
        PointF to_right = {100, 0};
        PointF to_top = {0, 100};
        painter->drawLine(abs_transform * (rel_pos_ + to_right + to_top), abs_transform * (rel_pos_ + to_right - to_top));
        painter->drawLine(abs_transform * (rel_pos_ + to_right + to_top), abs_transform * (rel_pos_ - to_right + to_top));
        painter->drawLine(abs_transform * (rel_pos_ - to_right + to_top), abs_transform * (rel_pos_ - to_right - to_top));
        painter->drawLine(abs_transform * (rel_pos_ - to_right - to_top), abs_transform * (rel_pos_ + to_right - to_top));
        return 0;
    }
    ~GraphicsRectangleItem() {}
};


#endif