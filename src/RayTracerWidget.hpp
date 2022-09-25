#ifndef RAY_TRACER_WIDGET_HPP
#define RAY_TRACER_WIDGET_HPP

#include "Widget.hpp"
#include "Vector3D.hpp"
#include "RayIntersectable.hpp"


class RayTracerWidget : public Widget {
private:
    double FOV_ = M_PI / 2;
    double view_plane_dist_;
    
    double recalc_view_plane_dist();
    Ray    calc_ray_direction(int x, int y);
    
public:
    RayTracerWidget(double FOV, 
                    const Rect& rect, 
                    const Point& point, 
                    Widget* parent=nullptr);

    RayTracerWidget(const Rect& rect, const Point& point, Widget* parent=nullptr);

    // RayTracerWidget(const )
    // int paint(Painter* painter); //FIX
    Vector3D camera_pos_ = {0, 0, 0};
    Vector3D camera_direction_ = {0, 0, 1};

};

#endif