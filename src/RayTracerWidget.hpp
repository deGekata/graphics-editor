#ifndef RAY_TRACER_WIDGET_HPP
#define RAY_TRACER_WIDGET_HPP

#include "Widget.hpp"
#include "Vector3D.hpp"
#include "RayIntersectable.hpp"

#define LAMBERT_RAY_CNT 5

class RayTracerWidget : public Widget {
public:
    double FOV_ = M_PI / 2;
    double view_plane_dist_;
    Vector3D plane_coord_x_;
    Vector3D plane_coord_y_;
    
    short int depth_ = 10;
    short int lambert_depth_delta = 5;
    short int lambert_ray_cnt = 5;
    double lambert_coefficient = 0.05 / lambert_ray_cnt; 

    void   recalc_view_plane_dist();

    inline Ray calc_ray_direction(int x, int y);
    ColorF trace_ray(const Ray& ray, short int depth);
    ColorF trace_lambert(const Ray& ray, const Vector3D& normal, double distance, short int depth);

    Intersection get_min_intersection_object(const Ray& ray);

    std::vector<RayIntersectableBasic*> scene_items;

public:
    RayTracerWidget(double FOV, 
                    const Rect& rect, 
                    const Point& point, 
                    Widget* parent=nullptr);

    RayTracerWidget(const Rect& rect, const Point& point, Widget* parent=nullptr);

    bool add_item(RayIntersectableBasic* n_item);

    // RayTracerWidget(const )
    int paint(Painter* painter); //FIX:
    Vector3D camera_pos_ = {0, 0, 0};
    Vector3D camera_direction_ = {0, 0, 1};

};

#endif