#include "WidgetModifier.hpp"
#include "Events/Event.hpp"

WidgetModifier::WidgetModifier(Rect rect, Point point) 
    :
    self_surface_(rect.size_.x_, rect.size_.y_),
    buff_surface_(rect.size_.x_, rect.size_.y_)
    // ,buffer_surface_(rect.size_.x_, rect.size_.y_),
{
    rect_ = rect;
    pos_ = point;
    constraints_ = rect_;
}

int WidgetModifier::repaint(Painter* painter) {
    //TODO:
    if (painter == NULL) return 1;
    
    repaint_(painter);
    this->self_surface_.blitToOther(&this->rect_, painter->window_surface_, &painter->window_rect_);
    
    for (size_t it = 0; it < items.size(); ++it) {
        items[it]->repaint(painter);
    }

    return 0;
}

int WidgetModifier::update(Painter* painter) {
    if (painter == NULL) {
        std::cout << "bug";
        return 1;
    }
    //TODO:
    bool need_to_blit = this->update_(painter);
    
    // this->self_surface_.blitToOther(&this->rect_, &this->buff_surface_, &this->rect_);
    

    return need_to_blit || need_to_blit_child;
}

Point WidgetModifier::mapFromGlobal(Point pos) {
    if (this->parent_ == NULL) return pos - this->pos_;
    return parent_->mapFromGlobal(pos) - this->pos_; 
}

Point WidgetModifier::mapToGlobal(Point pos) {
    if (this->parent_ == NULL) return pos;
    return parent_->mapToGlobal(pos + this->pos_);
}

Point WidgetModifier::mapFromParent(Point pos) {
    if (parent_ == NULL) return pos;
    return pos - this->pos_;
}

Point WidgetModifier::mapToParent(Point pos) {
    if (this->parent_ == NULL) return pos;
    return pos + this->pos_;
}

bool WidgetModifier::isInConstraints(Point pos) {
    return this->constraints_.inRect(pos);
}

int Widget::keyPressEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "mod\n";
    return 0;
}

int WidgetModifier::keyReleaseEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "mod\n";
    return 0;
}

int WidgetModifier::mousePressEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "mod\n";
    return 0;
}

int WidgetModifier::mouseReleaseEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "mod\n";
    return 0;
}

int WidgetModifier::mouseMoveEvent(Event* event) {
    // std::cout << __PRETTY_FUNCTION__ << "mod\n";
    return 0;
}

int WidgetModifier::mouseEnterEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "mod\n";
    return 0;
}

int WidgetModifier::mouseLeaveEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "mod\n";
    return 0;
}