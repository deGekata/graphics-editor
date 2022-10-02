#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "BasicObject.hpp"
#include "Painter.hpp"
#include "Utilities.hpp"

#include <vector>

//widget can be drawn
class Widget : public BasicObject {
protected:
    virtual int paint(Painter* painter) {};
public:
    Widget(const RectF& rect, const PointF& point, Widget* parent=nullptr);

    int repaint(Painter* painter);
    int addChild(Widget* child, PointF pos);


    #pragma region positioning
    //positioning region
    Transformation absTransformToParent();

    Transformation absTransformFromParent();

    PointF absPos(const PointF& pos_in_this);
    //end positioning region
    #pragma endregion

    std::vector<Widget*> items;
    Widget* parent_ = nullptr;

    RectF rect_ = {0, 0};
    PointF pos_ = {0, 0};

};


#endif