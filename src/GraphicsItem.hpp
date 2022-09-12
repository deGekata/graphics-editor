#ifndef GRAPHICS_ITEM_HPP
#define GRAPHICS_ITEM_HPP

#include "Utilities.hpp"
#include "Painter.hpp"


class GraphicsItem {
public:
    GraphicsItem() = default;
    // virtual ~GraphicsItem() = 0;
    virtual int paint(Painter* painter) = 0;
    // virtual void pos()  = 0;
    
    virtual const Rect& boundingRect() const { return rect_; };
    
    int addChild(GraphicsItem* item, Point pos) {
        if (item == NULL) return 1;
        item->parent_ = this;
        item->parent_delta_coords_ = pos;
        return 0;
    }

    Transformation absTransformToParent() {
        if (parent_ == NULL) return Transformation(parent_delta_coords_, -rotation_angle_);
         
        return parent_->absTransformToParent() * Transformation(parent_delta_coords_, -rotation_angle_);
    }

    Transformation absTransformFromParent() {
        if (parent_ == NULL) return Transformation(-parent_delta_coords_, rotation_angle_);
         
        return Transformation(-parent_delta_coords_, rotation_angle_) * parent_->absTransformFromParent();
    }

    Transformation transformOnParent() {
        return Transformation(parent_delta_coords_, -rotation_angle_);
    }

    Point absPos(const Point& pos_in_this) {
        if (parent_ == NULL) return pos_in_this;

        return absTransformToParent() * pos_in_this;
    }
    
    Point mapOnParent(const Point& point) {
        Transformation transformation(parent_delta_coords_, -rotation_angle_);
        // std::cout << transformation << '\n';
        // std::cout << point << '\n';
        // std::cout << parent_base_point << '\n';
        // Point pnt = transformation * point;
        // std::cout << "pnt res" << pnt << "\n";
        return transformation * point;
    }

    GraphicsItem* parent_ = NULL;
    
    Rect rect_ = {0, 0};
    Point parent_delta_coords_ = {0, 0};
    
    bool is_parent_bounded = false;
    double scale_x_ = 1.0, scale_y_ = 1.0;
    double rotation_angle_ = 0;
};


#endif