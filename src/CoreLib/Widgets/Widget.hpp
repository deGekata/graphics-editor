#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "BasicObject.hpp"
#include "Painter.hpp"
#include "Utilities.hpp"
#include "Surface.hpp"
// #include "Events/Events.hpp"

#include <vector>
#include <list>
//widget can be drawn
class Painter;
class EventManager;
class WidgetModifier;
class ModifierList;
class Widget {
private:
public:
    bool hasChanged_ = true;
    EventManager* event_manager = NULL;

    virtual int repaint_(Painter* painter) { UNUSED(painter); return 0;};
    virtual int repaint(Painter* painter);

    virtual int update_(Painter* painter) { UNUSED(painter); return 0;};
    virtual int update(Painter* painter);
    Widget(Rect rect, Point point, EventManager* manager, Widget* parent);
public:
    Widget(Rect rect, Point point, Widget* parent=nullptr);

    Surface* getBuffSurface();

    int addChild(Widget* child, Point pos);
    int modify(WidgetModifier* modifier);
    //events region

    virtual int processSelfEvent(Event* event);

    virtual int keyPressEvent(Event* event);

    virtual int keyReleaseEvent(Event* event);

    virtual int mousePressEvent(Event* event);

    virtual int mouseReleaseEvent(Event* event);

    virtual int mouseMoveEvent(Event* event);

    virtual int mouseEnterEvent(Event* event);

    virtual int mouseLeaveEvent(Event* event);

    //end events region 

    //positioning region
    Transformation absTransformToParent();
    Transformation absTransformFromParent();
    PointF         absPos(const PointF& pos_in_this);
    Point          mapFromGlobal(Point pos);
    Point          mapToGlobal(Point pos);
    Point          mapFromParent(Point pos);
    Point          mapToParent(Point pos);
    Point          mapProcessModifiers(Point pos);
    Point          mapRevertModifiers(Point pos);
    Point          getPos();
    Rect           getRectModified();
    bool           isInConstraints(Point pos);
    //end positioning region

    std::vector<Widget*> items;

    Widget* parent_ = nullptr;
    
    ModifierList* modifier_list_ = nullptr;
    Rect rect_ = {0, 0};
    Rect constraints_ = {0, 0};
    Point pos_ = {0, 0}; // position in parent coordinates
    Surface self_surface_; 
    Surface buff_surface_;
    // Surface buffer_surface_
    friend class Painter;

};


#endif




