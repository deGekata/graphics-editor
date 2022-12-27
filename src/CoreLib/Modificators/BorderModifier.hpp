#ifndef BORDER_WIDGET_MODIFIER
#define BORDER_WIDGET_MODIFIER
#include "WidgetModifier.hpp"

// #define BORDER_WIDTH 10

class BorderModifier : public WidgetModifier {
public:

    explicit BorderModifier(Rect rect, size_t border_width = 5) : 
        border_width_(border_width),
        WidgetModifier(Rect({0, 0}, rect.size_ + Point(border_width * 2, border_width * 2)), Point(border_width, border_width)) 
    {   
        constraints_.size_ = constraints_.size_ + Point(2 * border_width, 2 * border_width);
        constraints_.point_ = constraints_.point_ - Point(border_width, border_width);
        std::cout << rect_.size_ << " " << rect_.point_ << "\n";
        full_focus_color_ = ColorF(255, 255, 255, 255);
    }

    Point underlyingBasePos() override {
        return Point(border_width_, border_width_);
    }

    virtual int mouseMoveEvent(Event* event) override {
        UNUSED(event);
        return 0;
    }

    virtual int mouseEnterEvent(Event* event) override {
        UNUSED(event);
        return 0;
    }

    virtual int mouseLeaveEvent(Event* event) override {
        UNUSED(event);
        return 0;
    }
    
    int repaint_(Painter* painter) override {
        if (painter == nullptr) return -1;
        painter->begin(&this->self_surface_);
        painter->setColor(full_focus_color_);

        //simple draw borders
        painter->drawRectFill(0, 0, border_width_, rect_.size_.y_);
        painter->drawRectFill(0, 0, rect_.size_.x_, border_width_);
        painter->drawRectFill(0, rect_.size_.y_ - border_width_, rect_.size_.x_, rect_.size_.y_);
        painter->drawRectFill(rect_.size_.x_ - border_width_, 0, rect_.size_.x_, rect_.size_.y_);
        
        painter->setColor(ColorF(0, 0, 0, 0));
        //clear corners
        painter->drawRectFill(0, 0, border_width_, border_width_); //left top
        painter->drawRectFill(rect_.size_.x_ - border_width_, 0, rect_.size_.x_, border_width_); //right top
        painter->drawRectFill(0, rect_.size_.y_ - border_width_, border_width_, rect_.size_.y_); //left bottom
        painter->drawRectFill(rect_.size_.x_ - border_width_, rect_.size_.y_ - border_width_, rect_.size_.x_, rect_.size_.y_); //right bottom

        //draw circles
        painter->setColor(full_focus_color_);
        painter->drawCircleFill(border_width_, border_width_, border_width_ + 2); //left top
        painter->drawCircleFill(rect_.size_.x_ - border_width_, border_width_, border_width_ + 2); //right top
        painter->drawCircleFill(border_width_, rect_.size_.y_ - border_width_, border_width_ + 2); //left bottom
        painter->drawCircleFill(rect_.size_.x_ - border_width_, rect_.size_.y_ - border_width_, border_width_ + 2); //right bottom

        //clean center
        painter->setColor(ColorF(0, 0, 0, 0));
        painter->drawRectFill(border_width_, border_width_, rect_.size_.x_ - 2 * border_width_, rect_.size_.y_ - 2 * border_width_);
        painter->end();
        hasChanged_ = false;
        // std::cout << "repaint border\n";
        return 1;
    }

    int update_(Painter* painter) override {
        if (painter == nullptr) return -1;
        if (hasChanged_) {
            this->repaint_(painter);
            hasChanged_ = false;
            std::cout << "repaint border\n";
            return 1;
        }
        return 0;
    }
    
    ColorF full_focus_color_ = ColorF(255, 255, 255, 255);
    size_t border_width_ = 0;
};


#endif