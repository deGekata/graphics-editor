#ifndef HOVER_WIDGET_MODIFIER
#define HOVER_WIDGET_MODIFIER
#include "WidgetModifier.hpp"

// #define BORDER_WIDTH 10

class HoverModifier : public WidgetModifier {
public:

    explicit HoverModifier(Rect rect, size_t border_width = 5) : 
        border_width_(border_width),
        WidgetModifier(Rect({0, 0}, rect.size_), {0, 0}) 
    {   
        //pass
    }

    Point underlyingBasePos() override {
        return Point(0, 0);
    }

    virtual int mouseMoveEvent(Event* event) override {
        int x =  abs(event->mouse_motion.pos.x_ - (constraints_.size_.x_+ 2 * constraints_.point_.x_) / 2 );
        int y =  abs(event->mouse_motion.pos.y_ - (constraints_.size_.y_+ 2 * constraints_.point_.x_) / 2 );
        
        double multiplier = std::min(1.0, 2.0 * std::max(abs(x) / (double)constraints_.size_.x_, abs(y) / (double)constraints_.size_.y_));
        multiplier = std::pow(1.0 - multiplier, 1.0 / 2.0);
        cur_color_ = full_focus_color_ * multiplier;
        hasChanged_ = true;
        // std::cout << "move border\n";
        return 0;
    }

    virtual int mouseEnterEvent(Event* event) override {
        UNUSED(event);
        hasChanged_ = true;
        cur_color_ = full_focus_color_ * 0.0;

        std::cout << "enter border\n";
        return 0;
    }

    virtual int mouseLeaveEvent(Event* event) override {
        UNUSED(event);
        cur_color_ = full_focus_color_ * 0.0;
        hasChanged_ = true;
        
        std::cout << "leave border\n";
        return 0;
    }
    
    int repaint_(Painter* painter) override {
        if (painter == nullptr) return -1;
        painter->begin(&this->self_surface_);
        painter->setColor(cur_color_);

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
        painter->setColor(cur_color_);
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
    ColorF cur_color_ = full_focus_color_ * 0.0;
    size_t border_width_ = 0;
};


#endif