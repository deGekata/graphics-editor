#include "Widget.hpp"

Widget::Widget(const RectF& rect, const PointF& point, Widget* parent) {
    rect_ = rect;
    pos_ = point;
    if (parent != nullptr) {
        parent->addChild(this, point);
    }
}

int Widget::repaint(Painter* painter) {
    if (painter == NULL) return 1;
    
    for (size_t it = 0; it < items.size(); ++it) {
        items[it]->paint(painter);
    }

    return 0;
}

int Widget::addChild(Widget* child, PointF pos) {
    if (child == nullptr) return 1;
    child->rect_ = RectF::min_rect(rect_, child->rect_, pos);
    items.push_back(child);
    child->parent_ = this;
    return 0;
}


