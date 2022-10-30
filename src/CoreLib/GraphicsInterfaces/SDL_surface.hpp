#ifndef GRAPHICS_INTERFACES_SLD_SURFACE_HPP
#define GRAPHICS_INTERFACES_SLD_SURFACE_HPP

#include "SDL.h"
#include "SDL_opengl.h"
#include <stdio.h>




class Surface_ {
private:
    SDL_Surface* surface_ = NULL;
    SDL_Rect* clip_rect = NULL;
public:
    
    Surface_(int width, int height) {
        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            surface_ = SDL_CreateRGBSurface(0, width, height, 32,
                                   0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff); 
        #else
            surface_ = SDL_CreateRGBSurface(0, width, height, 32,
                                   0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000); 
        #endif            
    }
    
    
    
    int blitToOtherSurface(SDL_Surface* dest, SDL_Rect* dest_rect) {
        return SDL_BlitSurface(this->surface_, this->clip_rect, dest, dest_rect);
    }

    
    ~Surface_() {
        //how to delete surface...
        SDL_FreeSurface(surface_);
        
        surface_ = NULL;
        return;
    }

    friend class Painter;
};


#endif