#ifndef VECTOR_2D
#define VECTOR_2D

#include "..\SDL2\include\SDL2\SDL.h"
#include <stdio.h>

class CoordSys;

class Vec2D {
public:
    Vec2D(int x, int y) : 
        x_(x), 
        y_(y) 
        {};

    Vec2D() {}; //TODO:

    int getX() const { return x_; }
    int getY() const { return y_; }

    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }

    Vec2D operator+(const Vec2D& s) const { return Vec2D(x_ + s.x_, y_ + s.y_); }
    Vec2D operator-(const Vec2D& s) const { return Vec2D(x_ - s.x_, y_ - s.y_); }
    Vec2D operator*(int mul)        const { return Vec2D(x_ * mul,  y_ * mul ); }

    
private:
    int x_ = 0, y_ = 0;
};



class CoordSys {
public:
    CoordSys() {}; //TODO:
    CoordSys(int x0, int y0, int width, int height);
    CoordSys(Vec2D size, Vec2D base_point);

    int drawVec(SDL_Renderer* renderer, const CoordSys& base_coords, Vec2D vec);

    Vec2D calcRealSize(const CoordSys& base_coords, const Vec2D& vec);
public:
    Vec2D size_, base_point_;



};


#endif