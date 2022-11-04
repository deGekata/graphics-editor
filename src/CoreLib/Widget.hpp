#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "BasicObject.hpp"
#include "Painter.hpp"
#include "Utilities.hpp"
#include "Surface.hpp"

#include <vector>

//widget can be drawn
class Painter;

class Widget : public BasicObject {
private:
public:
    bool hasChanged_ = true;
    virtual int repaint_(Painter* painter) { UNUSED(painter); return 1;};
    virtual int repaint(Painter* painter) final;

    virtual int update_(Painter* painter) { UNUSED(painter); return 1;};
    virtual int update(Painter* painter) final;
public:
    Widget(Rect rect, Point point, Widget* parent=nullptr);


    int addChild(Widget* child, Point pos);


    //positioning region
    Transformation absTransformToParent();

    Transformation absTransformFromParent();

    PointF absPos(const PointF& pos_in_this);
    //end positioning region

    std::vector<Widget*> items;
    Widget* parent_ = nullptr;

    Rect rect_ = {0, 0};
    Point pos_ = {0, 0};
    Surface self_surface_;
    Surface buff_surface_;
    // Surface buffer_surface_
    friend class Painter;

};


#endif