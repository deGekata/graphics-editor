#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <iostream>
#include "Utilities/Utilities.hpp"
// Surface_::  ~Surface_();
class Surface_;

class Surface {
private:
    Surface_* rsp_;
public:
    Surface() = delete;
    Surface(int width, int height);
    Surface(Surface_* new_rsp) : rsp_(new_rsp) {}

    int blitToOther(Rect* src_rect, Surface* dest_surface, Rect* dest_rect);
    int clear();
    ~Surface();
    friend class Window;
    friend class Painter;
};

#endif