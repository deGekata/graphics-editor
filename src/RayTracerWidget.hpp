#ifndef RAY_TRACER_WIDGET_HPP
#define RAY_TRACER_WIDGET_HPP

#include "Widget.hpp"
#include "Vector3D.hpp"



class RayTrace : public Widget {
private:
    double FOV = M_PI / 2;
    double view_plane_dist = 100;
    


public:
    RayTrace(const )
    int paint(Painter* painter); //FIX
    Vector3D camera_pos = {0, 0, 0};
    Vector3D camera_direction = {0, 0, 1};

};

#endif