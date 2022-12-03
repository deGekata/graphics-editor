#ifndef RAY_TRACER_WIDGET_HPP
#define RAY_TRACER_WIDGET_HPP

#include "CoreLib/Widgets/Widget.hpp"
#include "Vector3D.hpp"
#include "RayIntersectable.hpp"
#include <omp.h>
#include "SDL.h"
#include "SignalSlots.hpp"

typedef unsigned char BYTE;

#define LAMBERT_RAY_CNT 5

#pragma omp declare \
            reduction(ColorPlus: ColorF: \
                omp_out += omp_in)

#define AMBIENT ColorF(0.09, 0.09, 0.09)


class RayTracerWidget : public Widget {
public:
    double FOV_ = M_PI / 2;
    double view_plane_dist_;
    Vector3D plane_coord_x_;
    Vector3D plane_coord_y_;
    
    short int depth_ = 5;
    short int lambert_depth_delta = 7;
    short int lambert_ray_cnt = 10;
    double lambert_coefficient = 0.54 / lambert_ray_cnt; 


    inline Ray calc_ray_direction(int x, int y);
    ColorF trace_ray(const Ray& ray, short int depth);
    ColorF trace_lambert(const Ray& ray, const Vector3D& normal, double distance, short int depth);

    Intersection get_min_intersection_object(const Ray& ray);
    RayIntersectableBasic* get_cur_surrounding(const Vector3D& point);
    std::vector<RayIntersectableBasic*> scene_items;
    Signal<> tmp  = {};
public:
    void testfunc();
    int mouseEnterEvent(Event* event) {
        std::cout << "tracer enter\n";
        return 0;
    }

    int mouseLeaveEvent(Event* event) {
        std::cout << "tracer out\n";
        tmp();
        return 0;
    }

    int mouseMoveEvent(Event* event) {
        std::cout << "tracer move\n";
        return 0;
    }

    void   recalc_view_plane_dist();
    RayTracerWidget(double FOV, 
                    const Rect& rect, 
                    const Point& point, 
                    Widget* parent=nullptr);

    RayTracerWidget(const Rect& rect, const Point& point, Widget* parent=nullptr);

    bool add_item(RayIntersectableBasic* n_item);

    // RayTracerWidget(const )
    int update_(Painter* painter);
    int repaint_(Painter* painter); //FIX:
    Vector3D camera_pos_ = {0, 0, 0};
    Vector3D camera_direction_ = {0, 0, 1};
    ColorF* screen_buffer = nullptr;
    BYTE* scr_buff_ = nullptr;

};

#endif