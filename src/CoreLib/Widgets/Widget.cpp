#include "Widget.hpp"
#include "Events/EventManager.hpp"
#include "WidgetModifier.hpp"

Widget::Widget(Rect rect, Point point, EventManager* manager=new EventManager(), Widget* parent=nullptr) 
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
    this->event_manager = manager;
    modifier_list_ = new ModifierList();
    manager->objective_ = this;
}

Widget::Widget(Rect rect, Point point, Widget* parent) 
    :
    Widget(rect, point, new EventManager(), parent)
{}

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
    //TODO:
    bool need_to_blit = this->update_(painter);
    
    bool need_to_blit_child = false;
    bool need_to_blit_modifier = false;
    for (size_t it = 0; it < items.size(); ++it) {
        // std::cout << it << " lol\n";
        bool res = items[it]->update(painter);
        need_to_blit_child = need_to_blit_child || res;
    }

    if (need_to_blit_child || need_to_blit) {
        this->buff_surface_.clear();
        this->self_surface_.blitToOther(NULL, &this->buff_surface_, NULL);

        for (size_t it = 0; it < items.size(); ++it) {
            // items[it]->buff_surface_.blitToOther(&items[it]->rect_, &this->buff_surface_, &this->rect_);
            Rect dest_rect = {items[it]->getPos(), {0, 0}};
            items[it]->getBuffSurface()->blitToOther(NULL, &this->buff_surface_,  &dest_rect);
        }
    }

    if (modifier_list_->cnt != 0) {
        need_to_blit_modifier = modifier_list_->top->update(painter);
    }
    
    return need_to_blit || need_to_blit_child || need_to_blit_modifier;
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

int Widget::modify(WidgetModifier* modifier) {
    modifier->target_widget_ = this;
    if (modifier_list_->cnt == 0) {
        modifier->pos_ = this->pos_;
        this->pos_ = modifier->underlyingBasePos();
        modifier_list_->addModifier(modifier);
        return 0;
    }

    modifier->pos_ = this->modifier_list_->top->pos_;
    this->modifier_list_->top->pos_ = modifier->underlyingBasePos();
    modifier_list_->addModifier(modifier);
    return 0;
}

Point Widget::mapFromGlobal(Point pos) {
    if (this->parent_ == NULL) {
        pos = this->mapProcessModifiers(pos);
        return pos - this->pos_;
    }
    pos = this->mapProcessModifiers(parent_->mapFromGlobal(pos));
    return pos - this->pos_; 
}

Point Widget::mapToGlobal(Point pos) {
    pos = mapRevertModifiers(pos);
    if (this->parent_ == NULL) return pos;
    return parent_->mapToGlobal(pos + this->pos_);
}

Point Widget::mapFromParent(Point pos) {
    pos = mapProcessModifiers(pos);
    // if (parent_ == NULL) {
    //     return pos;
    // }
    return pos - this->pos_;
}

Point Widget::mapToParent(Point pos) {
    pos = mapRevertModifiers(pos);
    // if (this->parent_ == NULL) return pos;
    return pos + this->pos_;
}

Point Widget::mapProcessModifiers(Point pos) {
    if (modifier_list_->cnt == 0) return pos;
    return modifier_list_->bottom->mapFromTopModifier(pos);
}

Point Widget::mapRevertModifiers(Point pos) {
    if (modifier_list_->cnt == 0) return pos;
    return modifier_list_->top->mapFromBotModifier(pos);
}

bool Widget::isInConstraints(Point pos) {
    pos = mapProcessModifiers(pos);
    return this->constraints_.inRect(pos);
}

Rect Widget::getRectModified() {
    if (modifier_list_->cnt == 0) return rect_;
    return modifier_list_->top->rect_;
}

Point Widget::getPos() {
    if (modifier_list_->cnt == 0) return this->pos_;
    return modifier_list_->top->pos_;
}

Surface* Widget::getBuffSurface() {
    if (modifier_list_->cnt == 0) return &buff_surface_;
    return &(modifier_list_->top->buff_surface_);
}


int Widget::processSelfEvent(Event* event) {
    myAssert(event == NULL, "event must not be NULL");
    switch(event->type) {
        case EventType::KEYDOWN:{
            return keyPressEvent(event);
            break;
        }

        case EventType::KEYUP:{
            return keyReleaseEvent(event);
            break;
        }

        case EventType::MOUSEMOTION:{
            return mouseMoveEvent(event);
            break;
        }

        case EventType::MOUSE_ENTER:{
            return mouseEnterEvent(event);
            break;
        }

        case EventType::MOUSE_LEAVE:{
            return mouseLeaveEvent(event);
            break;
        }
        
        case EventType::MOUSEBUTTONDOWN:{
            return mousePressEvent(event);
            break;
        }

        case EventType::MOUSEBUTTONUP:{
            return mouseReleaseEvent(event);
            break;
        }

        default:
            myAssert(false, "unknown event");
            break;
    }

    return false;
}

int Widget::keyPressEvent(Event* event) {
    (void)event;
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::keyReleaseEvent(Event* event) {
    (void)event;
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::mousePressEvent(Event* event) {
    (void)event;
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::mouseReleaseEvent(Event* event) {
    (void)event;
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::mouseMoveEvent(Event* event) {
    (void)event;
    // std::cout << __PRETTY_FUNCTION__ << "\n";
    // std::cout << event->mouse_motion.pos << "\n";
    return 0;
}

int Widget::mouseEnterEvent(Event* event) {
    (void)event;
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}

int Widget::mouseLeaveEvent(Event* event) {
    (void)event;
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return 0;
}