#include "SDL_painter.hpp"

#include "Core/Painter.hpp"
#include "Widgets/Widget.hpp"


Painter::Painter(Window* window) {
    rsp_ = new Painter_(window->rsp_);
}

Painter::~Painter() {
    delete rsp_;
}

void Painter::setWindow(Window* window) {
    rsp_->setWindow(window->rsp_);
    this->window_surface_ = window->surface_;
    this->window_rect_ = {0, 0, window->rect_.size_.x_, window->rect_.size_.y_};
    return;
}

int Painter::begin(Surface* surface) {
    rsp_->begin(surface->rsp_);
    return 0;
}

int Painter::end() {
    rsp_->end();
    return 0;
}

int Painter::fillWindow() {
    return rsp_->fillWindow();
}

int Painter::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return rsp_->setColor(r, g, b, a);
}

int Painter::setColor(const ColorF& color) {
    return rsp_->setColor(color);
}

void Painter::present() {
    rsp_->present();
    return;
}

int Painter::drawArrow(const PointF& p1, const PointF& p2) {
    return rsp_->drawArrow(p1, p2);
}

int Painter::drawLine(PointF p1, PointF p2) {
    return rsp_->drawLine(p1, p2);
}

int Painter::drawLine(int x1, int y1, int x2, int y2) {
    return rsp_->drawLine(x1, y1, x2, y2);
}

int Painter::drawPoint(PointF p1) {
    return rsp_->drawPoint(p1);
}

int Painter::drawPoint(int x, int y) {
    return rsp_->drawPoint(x, y);
}

int Painter::drawPointBounded(int x, int y) {
    //....
    UNUSED(x);
    UNUSED(y);
    return 1;
}