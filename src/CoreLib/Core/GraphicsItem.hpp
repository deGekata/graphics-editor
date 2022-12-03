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
    
    GraphicsItem(GraphicsItem* item) : parent_(item) {};
    
    int addChild(GraphicsItem* item, PointF pos) {
        if (item == NULL) return 1;
        item->parent_ = this;
        item->parent_delta_coords_ = pos;
        return 0;
    }
    
    virtual const RectF& boundingRect() const { return rect_; };

    //{ region positioning
    Transformation absTransformToParent() {
        if (parent_ == NULL) return Transformation(parent_delta_coords_, -rotation_angle_);
    
        return parent_->absTransformToParent() * Transformation(parent_delta_coords_, -rotation_angle_);
    }

    Transformation absTransformFromParent() {
        return absTransformToParent().inverse();
    }

    PointF absPos(const PointF& pos_in_this) {
        if (parent_ == NULL) return pos_in_this;

        return absTransformToParent() * pos_in_this;
    }
    //}

// MappableObject* parent cringeeeee
    GraphicsItem* parent_ = NULL;
    
    RectF rect_ = {0, 0};
    PointF parent_delta_coords_ = {0, 0};
    
    bool is_parent_bounded = false;
    double scale_x_ = 1.0, scale_y_ = 1.0;
    double rotation_angle_ = 0;
};


#endif