#include "vectord_2d.hpp"




CoordSys::CoordSys(int x0, int y0, int width, int height) :
    base_point_(x0, y0),
    size_(width, height)
{
    // SDL_Log("%d lel\n", width);
    // base_point_.setX(x0);
    // base_point_.setY(y0);
    // size_.setX(width);
    // size_.setY(height);
    // SDL_Log("%d lel\n", size_.getY());

}

CoordSys::CoordSys(Vec2D size, Vec2D base_point) {
    size_ = size;
    base_point_ = base_point;
}

int CoordSys::drawVec(SDL_Renderer* renderer, const CoordSys& base_coords, Vec2D vec) {
    if (renderer == nullptr) return 1;
    // SDL_Log("lol");
    // printf("lol");
    Vec2D relative_vec = calcRealSize(base_coords, vec);
    Vec2D line_begin = base_coords.base_point_ + base_point_;
    // printf("kek");
    // SDL_Log("base x0 %d y0 %d x1 %d y1 %d\n", base_coords.base_point_.getX(), base_coords.base_point_.getY(), base_coords.size_.getX(), base_coords.size_.getY());
    // SDL_Log("res x0 %d y0 %d x1 %d y1 %d\n", line_begin.getX(), line_begin.getY(), line_begin.getX() + relative_vec.getX(), line_begin.getY() + relative_vec.getY());
    // return 0;
    return SDL_RenderDrawLine
                      (renderer, 
                       line_begin.getX(), line_begin.getY(),
                       line_begin.getX() + relative_vec.getX(), line_begin.getY() + relative_vec.getY()
                      );
}
    
Vec2D CoordSys::calcRealSize(const CoordSys& base_coords, const Vec2D& vec) {
    Vec2D ret_vec = vec;
    ret_vec.setX(ret_vec.getX() * (size_.getX() / base_coords.size_.getX()));
    ret_vec.setY(ret_vec.getY() * (size_.getY() / base_coords.size_.getY()));
    return ret_vec;
}