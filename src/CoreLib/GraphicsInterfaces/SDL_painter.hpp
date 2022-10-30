#ifndef GRAPHICS_INTERFACES_SLD_PAINTER_HPP
#define GRAPHICS_INTERFACES_SLD_PAINTER_HPP

#include "Utilities.hpp"
#include "SDL.h"
#include "SDL_window.hpp"

class Painter_ {
public:
    Painter_(Window_* window) {
        painter_ = SDL_CreateRenderer(window->window, -1, 0);
        if (painter_ == NULL) {
            printf("fdasdasfdsafdsafdsafsad");
            throw; //TODO:
        }
    }

    ~Painter_() {
        printf("dtoooooooooooooooor\n");
        if (painter_ != NULL) {
            SDL_DestroyRenderer(painter_);
        }
    }

    void begin(Surface_)

    void setWindow(Window_* window) {
        if (painter_ != NULL) {
            SDL_DestroyRenderer(painter_);
        }
        painter_ = SDL_CreateRenderer(window->window, -1, 0);
    }

    int fillWindow() {
        return SDL_RenderClear(painter_);
    }

    int fillWindowBounded() {
        return SDL_RenderFillRectF(painter_, &rect_);
    }

    int setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        if (painter_ == NULL) {
            printf("fucking nuuuuuuuul%d\n", __LINE__);
            exit(-1);
        }
        r = SDL_SetRenderDrawColor(painter_, r, g, b, a);
        return r;
        // return SDL_SetRenderDrawColor(painter_, r, g, b, a);
    }

    int setColor(const ColorF& color) {
        if (painter_ == NULL)
            printf("fucking nuuuuuuuul%d\n", __LINE__);
        return SDL_SetRenderDrawColor(painter_, uint8_t(color.r_ * 255), uint8_t(color.g_ * 255), uint8_t(color.b_ * 255), uint8_t(color.a_ * 255));
    }

    void present() {
        SDL_RenderPresent(painter_);
    }

    

    void setConstraint(const RectF& rect, const PointF& point) {
        rect_.x = rect.p1_.x_ + point.x_;   
        rect_.y = rect.p1_.y_ + point.y_;
        rect_.w = rect.p2_.x_ - rect.p2_.x_;
        rect_.h = rect.p2_.y_ - rect.p1_.y_;
    }

    int drawArrow(const PointF& p1, const PointF& p2) {
        PointF perpen  = (p2 - p1).rotate(0.5 * M_PI) / ((p2 - p1).len() / 20);
        PointF direction = (p2 - p1) / 5;

        drawLine(p1, p2);
        drawLine(p2, p2 - (direction + perpen));
        drawLine(p2, p2 - (direction - perpen));
        return 0;
    }

    int drawLine(PointF p1, PointF p2) {
        return drawLine(p1.x_, p1.y_, p2.x_, p2.y_);
    }

    int drawLine(int x1, int y1, int x2, int y2) { 
        
        return SDL_RenderDrawLine(painter_, x1, y1, x2, y2);
    }

    int drawLineBounded(int x1, int y1, int x2, int y2) { 
        if (x1 > x2) {
            SWAP(int, x1, x2);
            SWAP(int, y1, y2);
        }

        return 1;
    }
    
    int drawPoint(PointF p1) {
        return drawPoint(p1.x_, p1.y_);
    }

    int drawPoint(int x, int y) {
        return SDL_RenderDrawPoint(painter_, x, y);
    }

    int drawPointBounded(int x, int y) {
        if (x < rect_.x || rect_.x + rect_.w < x || y < rect_.y || rect_.y + rect_.w < y) return 1;
        return SDL_RenderDrawPoint(painter_, x, y);
    }


    SDL_Renderer* painter_ = NULL;
    SDL_FRect rect_;
    PointF point_;
};



#endif