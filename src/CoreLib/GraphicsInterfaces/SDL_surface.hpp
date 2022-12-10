#ifndef GRAPHICS_INTERFACES_SLD_SURFACE_HPP
#define GRAPHICS_INTERFACES_SLD_SURFACE_HPP

#include "SDL.h"
#include "SDL_opengl.h"
#include <stdio.h>




class Surface_ {
private:
    SDL_Surface* surface_ = NULL;
    SDL_Rect clip_rect_;
    
public:
    
    Surface_(int width, int height) {
        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            surface_ = SDL_CreateRGBSurface(0, width, height, 32,
                                   0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff); 
        #else
            surface_ = SDL_CreateRGBSurface(0, width, height, 32,
                                   0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000); 
        #endif            
        SDL_SetSurfaceBlendMode(surface_, SDL_BLENDMODE_NONE);
        clip_rect_ = {0, 0, width, height};
        SDL_SetClipRect(surface_, &clip_rect_);
    }

    Surface_(SDL_Surface* other) {
        this->surface_ = other;
    }

    int height() {
        return surface_->h;
    }

    int width() {
        return surface_->w;
    }
    
    int blitToOther(SDL_Rect* src_rect, Surface_* dest, SDL_Rect* dest_rect) {
        return SDL_BlitSurface(this->surface_, src_rect, dest->surface_, dest_rect);
    }

    
    ~Surface_() {
        //how to delete surface...
        SDL_FreeSurface(surface_);
        printf("destructor of Surface_");
        surface_ = NULL;
        return;
    }

    // friend class Painter;
    friend class Painter_;
};


#endif