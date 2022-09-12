#ifndef PAINTER_HPP
#define PAINTER_HPP

#include "Utilities.hpp"
#include "..\SDL2\include\SDL2\SDL.h"
#include "Window.hpp"

class Painter {
public:
    Painter(const Window& window) {
        painter_ = SDL_CreateRenderer(window.window, -1, 0);
        if (painter_ == NULL) {
            throw; //TODO:
        }
    }

    ~Painter() {
        if (painter_ != NULL) {
            SDL_DestroyRenderer(painter_);
        }
    }

    void setWindow(const Window& window) {
        if (painter_ != NULL) {
            SDL_DestroyRenderer(painter_);
        }
        painter_ = SDL_CreateRenderer(window.window, -1, 0);
    }

    int fillWindow() {
        return SDL_RenderClear(painter_);
    }

    int setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        return SDL_SetRenderDrawColor(painter_, r, g, b, a);
    }

    void present() {
        SDL_RenderPresent(painter_);
    }


    void repaint();

    int drawLine(Point p1, Point p2) {
        return drawLine(p1.x_, p1.y_, p2.x_, p2.y_);
    }

    int drawLine(int x1, int y1, int x2, int y2) { 
        return SDL_RenderDrawLine(painter_, x1, y1, x2, y2);
    }
    
    int drawPoint(Point p1) {
        return drawPoint(p1.x_, p1.y_);
    }

    int drawPoint(int x, int y) {
        return SDL_RenderDrawPoint(painter_, x, y);
    }

    SDL_Renderer* painter_ = NULL;

};



#endif