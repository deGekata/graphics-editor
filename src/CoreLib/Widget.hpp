#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "BasicObject.hpp"
#include "Painter.hpp"
#include "Utilities.hpp"
#include "Surface.hpp"
// #include "Event.hpp"

#include <vector>

//widget can be drawn
class Painter;
class EventManager;

class Widget : public BasicObject {
private:
public:
    bool hasChanged_ = true;
    EventManager* event_manager = NULL;

    virtual int repaint_(Painter* painter) { UNUSED(painter); return 1;};
    virtual int repaint(Painter* painter) final;

    virtual int update_(Painter* painter) { UNUSED(painter); return 1;};
    virtual int update(Painter* painter) final;
public:
    Widget(Rect rect, Point point, Widget* parent=nullptr);


    int addChild(Widget* child, Point pos);

    //events region

    virtual int keyPressEvent(Event* event) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return 0;
    }

    virtual int keyReleaseEvent(Event* event) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return 0;
    }

    virtual int mousePressEvent(Event* event) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return 0;
    }

    virtual int mouseReleaseEvent(Event* event) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return 0;
    }

    virtual int enterEvent(Event* event) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return 0;
    }

    virtual int leaveEvent(Event* event) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return 0;
    }

    //end events region 

    //positioning region
    Transformation absTransformToParent();

    Transformation absTransformFromParent();

    PointF absPos(const PointF& pos_in_this);
    //end positioning region

    std::vector<Widget*> items;

    Widget* parent_ = nullptr;

    Rect rect_ = {0, 0};
    Rect constraints_ = {0, 0};
    Point pos_ = {0, 0};
    Surface self_surface_;
    Surface buff_surface_;
    // Surface buffer_surface_
    friend class Painter;

};


#endif