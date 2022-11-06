#ifndef GRAPHICS_INTERFACES_SLD_APP_HPP
#define GRAPHICS_INTERFACES_SLD_APP_HPP
#include "SDL.h"


class App_ {
private:
int startGraphicalLib() {
        static bool is_called = false;
        if (is_called) {
            // SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
            // SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
            SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1");
            return SDL_Init(SDL_INIT_EVERYTHING);
        }
        return 0;
    }

    static int stopGraphicalLib() {
        static bool is_called = false;
        if (is_called) {
            SDL_Quit();
        }
        return 0;
    }
    App_() {
        startGraphicalLib();
    }

    ~App_() {
        stopGraphicalLib();
    }

};


#endif
