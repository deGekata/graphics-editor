#ifndef GRAPHICS_INTERFACES_SLD_WINDOW_HPP
#define GRAPHICS_INTERFACES_SLD_WINDOW_HPP

#include "SDL.h"
#include <stdio.h>

class Window_ {
public:
    Window_(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0) {
        startGraphicalLib();
        window = SDL_CreateWindow("", x, y, width, height, flags | SDL_WINDOW_OPENGL);
    }


    SDL_Window* window;

    ~Window_() {
        printf("dtooooooooooooor-----------");
        SDL_DestroyWindow(window);
    }

    static int startGraphicalLib() {
        static bool is_called = false;
        if (is_called) {
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
    }
    friend class Window;
};


#endif