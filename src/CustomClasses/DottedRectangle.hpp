#ifndef DOTTED_RECTANGLE_HPP
#define DOTTED_RECTANGLE_HPP

#include "CoreLib/Core/GraphicsGeometryItem.hpp"


class DottedRectangle : public GraphicsGeometryItem {
public:
    DottedRectangle(GraphicsItem* parent = NULL) : GraphicsGeometryItem(parent) {};

    DottedRectangle(const PointF& pos, RectF rect = {-100, -100, 100, 100}) {
        rel_pos_.x_ = pos.x_;
        rel_pos_.y_ = pos.y_;
        rect_ = rect;
        // parent_base_point = pos;
    }

    int paint(Painter* painter) {
        if (painter == NULL) return 1;
        // PointF absolute_pos = absPos(pos_);
        // Transformation abs_transform = absTransformToParent();

        // PointF dx = { (rect_.p2_.x_ - rect_.p1_.x_) / line_cnt_, 0                    };
        // PointF dy = { 0,                                         (rect_.p2_.y_ - rect_.p1_.y_) / line_cnt_ };


        // for (int x = 0; x <= line_cnt_; ++x) {
        //     painter->drawLine(abs_transform * (rect_.p1_ + dx * x), abs_transform * (rect_.p2_ + dx * (x - line_cnt_)));
        // }
        // for (int y = 0; y <= line_cnt_; ++y) {
        //     painter->drawLine(abs_transform * (rect_.p1_ + dy * y), abs_transform * (rect_.p2_ + dy * (y - line_cnt_)));
        // }

        return 0;
    }

    const RectF& boundingRect() const {
        return rect_;
    };

    ~DottedRectangle() {}
    
    int line_cnt_ = 10;
};


#endif