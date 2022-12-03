#include "Widget.hpp"
#include "Events/EventManager.hpp"

Widget::Widget(Rect rect, Point point, Widget* parent) 
    :
    self_surface_(rect.size_.x_, rect.size_.y_),
    buff_surface_(rect.size_.x_, rect.size_.y_)
    // ,buffer_surface_(rect.size_.x_, rect.size_.y_),
{
    rect_ = rect;
    pos_ = point;
    constraints_ = rect_;
    if (parent != nullptr) {
        parent->addChild(this, point);
    }
    this->event_manager = new EventManager(this);
}

int Widget::repaint(Painter* painter) {
    if (painter == NULL) return 1;
    
    repaint_(painter);
    this->self_surface_.blitToOther(&this->rect_, painter->window_surface_, &painter->window_rect_);
    
    for (size_t it = 0; it < items.size(); ++it) {
        items[it]->repaint(painter);
    }

    return 0;
}

int Widget::update(Painter* painter) {
    if (painter == NULL) {
        std::cout << "bug";
        return 1;
    }

    bool need_to_blit = this->update_(painter);
    
    // this->self_surface_.blitToOther(&this->rect_, &this->buff_surface_, &this->rect_);
    bool need_to_blit_child = false;
    for (size_t it = 0; it < items.size(); ++it) {
        // std::cout << it << " lol\n";
        bool res = items[it]->update(painter);
        need_to_blit_child = need_to_blit_child || res;
    }

    if (need_to_blit_child || need_to_blit) {
        this->self_surface_.blitToOther(NULL, &this->buff_surface_, NULL);

        for (size_t it = 0; it < items.size(); ++it) {
            // items[it]->buff_surface_.blitToOther(&items[it]->rect_, &this->buff_surface_, &this->rect_);
            Rect dest_rect = {items[it]->pos_, {0, 0}};
            items[it]->buff_surface_.blitToOther(NULL, &this->buff_surface_,  &dest_rect);
        }
    }

    return need_to_blit || need_to_blit_child;
}

int Widget::addChild(Widget* child, Point pos) {
    if (child == nullptr) return 1;
    child->pos_ = pos;
    std::cout << pos << "poos\n";
    // child->rect_.point_ = pos;
    items.push_back(child);
    child->parent_ = this;
    return 0;
}

Point Widget::mapFromGlobal(Point pos) {
    if (this->parent_ == NULL) return pos - this->pos_;
    return parent_->mapFromGlobal(pos) - this->pos_; 
}

Point Widget::mapToGlobal(Point pos) {
    if (this->parent_ == NULL) return pos;
    return parent_->mapToGlobal(pos + this->pos_);
}

Point Widget::mapFromParent(Point pos) {
    if (parent_ == NULL) return pos;
    return pos - this->pos_;
}

Point Widget::mapToParent(Point pos) {
    if (this->parent_ == NULL) return pos;
    return pos + this->pos_;
}

bool Widget::isInConstraints(Point pos) {
    return this->constraints_.inRect(pos);
}








int Widget::keyPressEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::keyReleaseEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::mousePressEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::mouseReleaseEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::mouseMoveEvent(Event* event) {
    // std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::mouseEnterEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::mouseLeaveEvent(Event* event) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}