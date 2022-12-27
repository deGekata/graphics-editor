#ifndef WIDGET_MODIFIER_HPP
#define WIDGET_MODIFIER_HPP

#include "BasicObject.hpp"
#include "Painter.hpp"
#include "Utilities.hpp"
#include "Surface.hpp"


//widget can be drawn
class Painter;
class Widget;

class WidgetModifier : public Widget {
private:
public:

    virtual int repaint_(Painter* painter) override {UNUSED(painter); return 0;};
    virtual int repaint(Painter* painter)  override;

    virtual int update_(Painter* painter) override {UNUSED(painter); return 0;};
    virtual int update(Painter* painter) override;

public:
    WidgetModifier(Rect rect, Point point);

    //events region
    virtual int processSelfEvent(Event* event) override;
    
    virtual int keyPressEvent(Event* event) override;

    virtual int keyReleaseEvent(Event* event) override;

    virtual int mousePressEvent(Event* event) override;

    virtual int mouseReleaseEvent(Event* event) override;

    virtual int mouseMoveEvent(Event* event) override;

    virtual int mouseEnterEvent(Event* event) override;

    virtual int mouseLeaveEvent(Event* event) override;

    //end events region 

    //positioning region
    Transformation absTransformToParent();
    Transformation absTransformFromParent();
    PointF         absPos(const PointF& pos_in_this);
    Point          mapFromGlobal(Point pos);
    Point          mapToGlobal(Point pos);
    Point          mapFromParent(Point pos);
    Point          mapToParent(Point pos);

    Point          mapFromTopModifier(Point pos);   //TODO:
    Point          mapFromBotModifier(Point pos);//TODO:
    Point          mapFromParentModifier(Point pos);//TODO:
    Point          mapToParentModifier(Point pos);//TODO:
    
    virtual Point  underlyingBasePos();
    bool           isInConstraints(Point pos);
    //end positioning region

    WidgetModifier* child_mod_  = nullptr;
    WidgetModifier* parent_mod_ = nullptr;
    Widget* target_widget_      = nullptr;

    // Surface buffer_surface_
    friend class Painter;
};

struct ModifierList {
    // bottom mod
    WidgetModifier* bottom = nullptr;
    // top mod
    WidgetModifier* top = nullptr;
    size_t cnt = 0;
    ModifierList() {};

    void addModifier(WidgetModifier* modifier) {
        cnt++;
        if (bottom == nullptr) {
            bottom = top = modifier;
            modifier->child_mod_ = modifier->parent_mod_ = nullptr;
            return;
        }
        top->parent_ = modifier;
        modifier->child_mod_  = top;
        modifier->parent_mod_ = nullptr;
        top = modifier;
        return;
    }
};


#endif