#ifndef RAY_TRACER_WIDGET_HPP
#define RAY_TRACER_WIDGET_HPP

#include "Widget.hpp"
#include "Vector3D.hpp"
#include "RayIntersectable.hpp"
#include <omp.h>
typedef unsigned char BYTE;

#define LAMBERT_RAY_CNT 5

#pragma omp declare \
            reduction(ColorPlus: ColorF: \
                omp_out += omp_in)

#define AMBIENT ColorF(0.02, 0.02, 0.02)

class RayTracerWidget : public Widget {
public:
    double FOV_ = M_PI / 2;
    double view_plane_dist_;
    Vector3D plane_coord_x_;
    Vector3D plane_coord_y_;
    
    short int depth_ = 10;
    short int lambert_depth_delta = 10;
    short int lambert_ray_cnt = 20;
    double lambert_coefficient = 0.5 / lambert_ray_cnt; 


    inline Ray calc_ray_direction(int x, int y);
    ColorF trace_ray(const Ray& ray, short int depth);
    ColorF trace_lambert(const Ray& ray, const Vector3D& normal, double distance, short int depth);

    Intersection get_min_intersection_object(const Ray& ray);
    RayIntersectableBasic* get_cur_surrounding(const Vector3D& point);
    std::vector<RayIntersectableBasic*> scene_items;

public:
    void   recalc_view_plane_dist();
    RayTracerWidget(double FOV, 
                    const RectF& rect, 
                    const PointF& point, 
                    Widget* parent=nullptr);

    RayTracerWidget(const RectF& rect, const PointF& point, Widget* parent=nullptr);

    bool add_item(RayIntersectableBasic* n_item);

    // RayTracerWidget(const )
    int paint(Painter* painter); //FIX:
    Vector3D camera_pos_ = {0, 0, 0};
    Vector3D camera_direction_ = {0, 0, 1};
    ColorF* screen_buffer = nullptr;
    BYTE* scr_buff_ = nullptr;

};

#endif