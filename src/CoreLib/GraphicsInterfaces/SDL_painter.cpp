#include "SDL_painter.hpp"

#include "Painter.hpp"



Painter::Painter(const Window& window) {
    rsp_ = new Painter_(window.rsp_);
}

Painter::~Painter() {
        printf("dtooooooooooooor-----------");

    // delete rsp_;
}

void Painter::setWindow(const Window& window) {
    return rsp_->setWindow(window.rsp_);
}

int Painter::fillWindow() {
    return rsp_->fillWindow();
}

int Painter::fillWindowBounded() {
    // ....
    return 1;
}

int Painter::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return rsp_->setColor(r, g, b, a);
}

int Painter::setColor(const ColorF& color) {
    return rsp_->setColor(color);
}

void Painter::present() {
    rsp_->present();
}

void Painter::setConstraint(const RectF& rect, const PointF& point) {
    //....
    UNUSED(rect);
    UNUSED(point);
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

int Painter::drawLineBounded(int x1, int y1, int x2, int y2) {
    //.....
    UNUSED(x1);
    UNUSED(y1);
    UNUSED(x2);
    UNUSED(y2);
    return 1;
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