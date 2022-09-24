#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "..\SDL2\include\SDL2\SDL.h"

class Window {
public:
    Window(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0) {
        startGraphicalLib();
        window = SDL_CreateWindow("", x, y, width, height, flags | SDL_WINDOW_OPENGL);
    }


    SDL_Window* window;

    ~Window() {
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

    virtual void exec() {}
};


#endif