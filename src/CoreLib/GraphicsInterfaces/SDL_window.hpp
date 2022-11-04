#ifndef GRAPHICS_INTERFACES_SLD_WINDOW_HPP
#define GRAPHICS_INTERFACES_SLD_WINDOW_HPP

#include "SDL.h"
#include "SDL_opengl.h"
#include <stdio.h>
#include "SDL_surface.hpp"
class Window_ {
public:
    Window_(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0) {
        startGraphicalLib();
        window = SDL_CreateWindow("", x, y, width, height, flags | SDL_WINDOW_OPENGL);
        window_surface = SDL_GetWindowSurface(window);
    }

    

    SDL_Window*  window;
    SDL_Surface* window_surface;
    // SDL_GLContext gContext;
    
    
    ~Window_() {
        SDL_DestroyWindow(window);
    }

    static int startGraphicalLib() {
        static bool is_called = false;
        if (is_called) {
            // SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
            // SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
            SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1");
            return SDL_Init(SDL_INIT_EVERYTHING);
        }
        return 0;
    }

    static void stopGraphicalLib() {
        static bool is_called = false;
        if (is_called) {
            SDL_Quit();
        }
        return;
    }
    friend class Window;
};


#endif