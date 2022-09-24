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
    
    int addChild(GraphicsItem* item, Point pos) {
        if (item == NULL) return 1;
        item->parent_ = this;
        item->parent_delta_coords_ = pos;
        return 0;
    }
    
    virtual const Rect& boundingRect() const { return rect_; };

    #pragma region positioning
    //positioning region
    Transformation absTransformToParent() {
        if (parent_ == NULL) return Transformation(parent_delta_coords_, -rotation_angle_);
    
        return parent_->absTransformToParent() * Transformation(parent_delta_coords_, -rotation_angle_);
    }

    Transformation absTransformFromParent() {
        return absTransformToParent().inverse();
    }

    Point absPos(const Point& pos_in_this) {
        if (parent_ == NULL) return pos_in_this;

        return absTransformToParent() * pos_in_this;
    }
    //end positioning region
    #pragma endregion

    // #pragma region 

// dfasdfsad

// MappableObject* parent cringeeeee
    GraphicsItem* parent_ = NULL;
    
    Rect rect_ = {0, 0};
    Point parent_delta_coords_ = {0, 0};
    
    bool is_parent_bounded = false;
    double scale_x_ = 1.0, scale_y_ = 1.0;
    double rotation_angle_ = 0;
};


#endif