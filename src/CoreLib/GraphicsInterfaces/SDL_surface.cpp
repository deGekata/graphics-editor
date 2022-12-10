#include "SDL_surface.hpp"

#include "Core/Surface.hpp"


Surface::Surface(int width, int height)
{
    if (width <= 0 || height <= 0) {
        throw std::string("Surface size must be greater 0");
    }
    rsp_ = new Surface_(width, height);
}

Surface::~Surface() {
    delete this->rsp_;
}

int Surface::blitToOther(Rect* src_rect, Surface* dest_surface, Rect* dest_rect) {
    (void)src_rect;
    if (dest_rect == NULL) {
        return rsp_->blitToOther(NULL, dest_surface->rsp_, NULL);
    }
    // SDL_Rect src_rect_  = {0, 0, src_rect->size_.x_, src_rect->size_.y_};
    // SDL_Rect src_rect_  = {src_rect->point_.x_, src_rect->point_.y_, src_rect->size_.x_, src_rect->size_.y_};
    SDL_Rect dest_rect_ = {dest_rect->point_.x_, dest_rect->point_.y_, 0, 0};
    // SDL_Rect dest_rect_ = {dest_rect->point_.x_, dest_rect->point_.y_, dest_rect->size_.x_, dest_rect->size_.y_};
    // SDL_Rect src_rect_  = {300, 300, src_rect->size_.x_, src_rect->size_.y_};
    // SDL_Rect dest_rect_ = {0, 0, 0, 0};

    return rsp_->blitToOther(NULL, dest_surface->rsp_, &dest_rect_);
    // return rsp_->blitToOther(&src_rect_, dest_surface->rsp_, &dest_rect_);
}


