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

int Painter::drawRect(int x, int y, int width, int height) {
    return rsp_->drawRect(x, y, width, height);
}

int Painter::drawRect(PointF p1, PointF p2) {
    return rsp_->drawRect(p1, p2);
}

int Painter::drawRectFill(int x, int y, int width, int height) {
    return rsp_->drawRectFill(x, y, width, height);
}

int Painter::drawRectFill(PointF p1, PointF p2) {
    return rsp_->drawRectFill(p1, p2);
}

int Painter::drawPoint(PointF p1) {
    return rsp_->drawPoint(p1);
}

int Painter::drawPoint(int x, int y) {
    return rsp_->drawPoint(x, y);
}

int Painter::drawCircleFill(int cx, int cy, int radius)  {
    for (double dy = 1; dy <= radius; dy += 1.0) {
        double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
        int x = cx - dx;
        rsp_->drawLine(cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
        rsp_->drawLine(cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
    }
    return 0;
}

int Painter::drawPointBounded(int x, int y) {
    //....
    UNUSED(x);
    UNUSED(y);
    return 1;
}

int Painter::drawText(std::string& text, int x, int y, size_t size, const ColorF& color, std::string fontName) {
    //TODO:
    return 0;
}

int createTextSurface(const std::string& text, size_t size, const ColorF& color, const std::string fontName) {
    TTF_Font* font = TTF_OpenFont(fontName.c_str(), size);
    int curSize  = size;
    int realSize = 0;
    TTF_SizeText(font, text.c_str(), NULL, &realSize);

    while (realSize > size) {
        TTF_CloseFont(font);
        curSize--;
        font = TTF_OpenFont(fontName.c_str(), curSize);
        TTF_SizeText(font, text.c_str(), NULL, &realSize);
    }

    SDL_Color realColor = {color.r_, color.g_, color.b_, color.a_};
    SDL_Surface* message = TTF_RenderText_Blended(font, text.c_str(), realColor); 

    // SDL_Renderer* realRenderer = __theApp__->getRenderer()->getRealRenderer();

    // m_realTexture = SDL_CreateTextureFromSurface(realRenderer, message);
    // m_bounds = {0, 0, message->w, message->h};

    TTF_CloseFont(font);
    SDL_FreeSurface(message);
    return 0;
}