#include "WidgetModifier.hpp"
#include "Events/Event.hpp"
#include "ModifierEventManager.hpp"

WidgetModifier::WidgetModifier(Rect rect, Point point) 
    :
    Widget(rect, point, new ModifierEventManager(), nullptr)
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
    std::cout << "repaint\n";
    exit(0);
    return 0;
}

int WidgetModifier::update(Painter* painter) {
    if (painter == NULL) {
        std::cout << "bug";
        return 1;
    }
    //TODO:
    bool need_to_blit = this->update_(painter);

    if (child_mod_ == nullptr) {
        Rect dest_rect = {target_widget_->pos_, {0, 0}};
        this->buff_surface_.clear();
        target_widget_->buff_surface_.blitToOther(NULL, &this->buff_surface_,  &dest_rect);
    } else {
        child_mod_->update(painter);
        // std::cout << child_mod_->pos_ << "poooooos\n";
        Rect dest_rect = {child_mod_->pos_, {0, 0}};
        this->buff_surface_.clear();
        child_mod_->buff_surface_.blitToOther(NULL, &this->buff_surface_,  &dest_rect);
    }

    bool need_to_blit_child = false;
    for (size_t it = 0; it < items.size(); ++it) {
        // std::cout << it << " lol\n";
        bool res = items[it]->update(painter);
        need_to_blit_child = need_to_blit_child || res;
    }

    // if (need_to_blit_child || need_to_blit) {
    this->self_surface_.blitToOther(NULL, &this->buff_surface_, NULL);
    
    //possibly always no children
    for (size_t it = 0; it < items.size(); ++it) {
        // items[it]->buff_surface_.blitToOther(&items[it]->rect_, &this->buff_surface_, &this->rect_);
        Rect dest_rect = {items[it]->getPos(), {0, 0}};
        items[it]->getBuffSurface()->blitToOther(NULL, &this->buff_surface_,  &dest_rect);
    }
    //}

    //possibly always empty
    bool need_to_blit_mod = false;
    if (modifier_list_->cnt != 0) {
        modifier_list_->top->update(painter);
    }

    return true;
    // return need_to_blit || need_to_blit_child || need_to_blit_mod;
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
    // if (parent_ == NULL) return pos;
    return pos - this->pos_;
}

Point WidgetModifier::mapToParent(Point pos) {
    // if (this->parent_ == NULL) return pos;
    return pos + this->pos_;
}

bool WidgetModifier::isInConstraints(Point pos) {
    return this->constraints_.inRect(pos);
}

Point WidgetModifier::mapFromTopModifier(Point pos)    {
    if (parent_mod_ == nullptr) return pos;
    return  parent_mod_->mapFromTopModifier(pos) - this->pos_;
}

Point WidgetModifier::mapFromBotModifier(Point pos) {
    if (child_mod_ == nullptr) return pos;
    return child_mod_->mapFromBotModifier(pos) + this->pos_;
}

Point WidgetModifier::mapFromParentModifier(Point pos) {
    // if (parent_mod_ == nullptr) return pos;
    return pos - this->pos_;
}

Point WidgetModifier::mapToParentModifier(Point pos) {
    // if (parent_mod_ == nullptr) return pos;
    return pos + this->pos_;
}

Point  WidgetModifier::underlyingBasePos() {
    return {0, 0};
}

int WidgetModifier::processSelfEvent(Event* event) {
    // std::cout << __PRETTY_FUNCTION__ << "mod\n";
    switch(event->type) {
        case EventType::KEYDOWN:{
            keyPressEvent(event);
            break;
        }

        case EventType::KEYUP:{
            keyReleaseEvent(event);
            break;
        }

        case EventType::MOUSEMOTION:{
            mouseMoveEvent(event);
            break;
        }

        case EventType::MOUSE_ENTER:{
            mouseEnterEvent(event);
            break;
        }

        case EventType::MOUSE_LEAVE:{
            mouseLeaveEvent(event);
            break;
        }
        
        case EventType::MOUSEBUTTONDOWN:{
            mousePressEvent(event);
            break;
        }

        case EventType::MOUSEBUTTONUP:{
            mouseReleaseEvent(event);
            break;
        }

        default:
            myAssert(false, "unknown event");
            break;
    }
    return false;
}

int WidgetModifier::keyPressEvent(Event* event) {
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