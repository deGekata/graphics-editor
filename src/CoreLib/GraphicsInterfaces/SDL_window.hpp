#ifndef GRAPHICS_INTERFACES_SLD_WINDOW_HPP
#define GRAPHICS_INTERFACES_SLD_WINDOW_HPP

#include "SDL.h"
#include "SDL_opengl.h"
#include <stdio.h>
#include "SDL_surface.hpp"
class Window_ {
public:
    Window_(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0) {
        window = SDL_CreateWindow("", x, y, width, height, flags | SDL_WINDOW_OPENGL);
        window_surface = SDL_GetWindowSurface(window);
        SDL_SetSurfaceBlendMode(window_surface, SDL_BLENDMODE_NONE);
    }

    SDL_Window*  window;
    SDL_Surface* window_surface;    
    
    ~Window_() {
        SDL_DestroyWindow(window);
    }

    void updateWindowSurface() {
        SDL_UpdateWindowSurface(window);
    }

    uint32_t getWindowId() {
        return SDL_GetWindowID(window);
    }

    friend class Window;
};


#endif