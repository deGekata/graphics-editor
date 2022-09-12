#ifndef GRAPHICS_ARROW_HPP
#define GRAPHICS_ARROW_HPP

#include "GraphicsGeometryItem.hpp"


class GraphicsArrow : public GraphicsGeometryItem {
public:
    GraphicsArrow(GraphicsItem* parent = nullptr) {};

    GraphicsArrow(const Point& pos, Rect rect = {-100, -100, 100, 100}) {
        rel_pos_.x_ = pos.x_;
        rel_pos_.y_ = pos.y_;
        rect_ = rect;
        // parent_base_point = pos;
    }

    int paint(Painter* painter) {
        if (painter == NULL) return 1;

        Point base_point = rel_pos_ + (rect_.p1_ + rect_.p2_) / 2;
        Point direction  = (rect_.p2_ - base_point).normalize() * 50;
        Point end_point  = rel_pos_ + base_point + direction.normalize() * arrow_len;
        if (is_parent_bounded) {
            
        }
        // Point absolute_pos = absPos(pos_);
        Transformation abs_transform = absTransformToParent();
        // std::cout << abs_transform * (base_point) << "  arrow  " << abs_transform * end_point << " \n";
        painter->drawLine(abs_transform * (base_point), abs_transform * end_point);
        painter->drawLine(abs_transform * end_point, abs_transform * (end_point - direction.rotate(0.2 * M_PI)));
        painter->drawLine(abs_transform * end_point, abs_transform * (end_point - direction.rotate(-0.2 * M_PI)));

        return 0;
    }

    bool boundToParent() {
        if (parent_ != NULL) {
            rel_pos_ = {0, 0};
            rect_ = parent_->rect_;
            return is_parent_bounded = true;
        }
        return is_parent_bounded = false;
    }

    const Rect& boundingRect() const {
        return rect_;
    };

    ~GraphicsArrow() {}
    
    double arrow_len = 100;
};


#endif