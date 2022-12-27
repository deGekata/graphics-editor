#include "RayTracerWidget.hpp"
#include "Dump.h"

int RayTracerWidget::id = 0;

void RayTracerWidget::testfunc() {
    std::cout << "lolkek";
    return;
}


RayTracerWidget::RayTracerWidget
(
    double FOV, 
    const Rect& rect, 
    const Point& point, 
    Widget* parent
):
    Widget(rect, point, parent)
{
    if (is_zero(FOV - M_PI)) 
        throw;
    FOV_ = FOV;
    recalc_view_plane_dist();
    
    size_t max_x = rect.size_.x_;
    size_t max_y = rect.size_.y_;
    scr_buff_ = (BYTE*) calloc(max_x * max_y * 3, sizeof(char));
    ;
    tmp += METHOD(*this, RayTracerWidget::testfunc);
    id_ = id;
    id++;
    // rect_.p2_.x_ - rect.p1_.x_
    // screen_buffer = new ColorF[(rect_.p2_.x_ - rect.p1_.x_) * (rect_.p2_.y_ - rect.p1_.y_)];
}


RayTracerWidget::RayTracerWidget(
    const Rect& rect, 
    const Point& point, 
    Widget* parent
): 
   RayTracerWidget(M_PI / 2, rect, point, parent)
{

}

bool RayTracerWidget::add_item(RayIntersectableBasic* n_item) {
    if (n_item == nullptr) return true;
    
    for (size_t it = 0; it < scene_items.size(); ++it) {
        if (scene_items[it] == n_item) return true;
    }

    scene_items.push_back(n_item);
    return false;
}

void RayTracerWidget::recalc_view_plane_dist() {
    view_plane_dist_ = tan(M_PI / 2 - FOV_ / 2) * (rect_.size_.x_) / 2;
    camera_direction_ = camera_direction_.normalize();
    plane_coord_x_ = {
                camera_direction_.x_ * cos(M_PI / 2) - camera_direction_.z_ * sin(M_PI / 2),
                0,
                camera_direction_.x_ * sin(M_PI / 2) + camera_direction_.z_ * cos(M_PI / 2)
            };
    plane_coord_x_ = plane_coord_x_.normalize();
    // if (is_zero(camera_direction_.x_) && is_zero(camera_direction_.y_)) 
    //     plane_coord_x_ = Vector3D(1, 0, 0);
    // else 
    //     plane_coord_x_ = Vector3D(-camera_direction_.x_, camera_direction_.y_, 0).normalize();
    plane_coord_y_ = -(vectorMult(camera_direction_, plane_coord_x_).normalize());
}

inline Ray RayTracerWidget::calc_ray_direction(int x, int y) {
    // Ray ret_val = Ray(
    //     camera_pos_, 
    //     camera_direction_ * view_plane_dist_ + plane_coord_x_ * (x - (rect_.p2_.x_ - rect_.p1_.x_) /2) + plane_coord_y_ * (y - (rect_.p2_.y_ - rect_.p1_.y_) /2) );
    // return ret_val;
    return Ray(
        camera_pos_, 
        camera_direction_ * view_plane_dist_ + plane_coord_x_ * (x - rect_.size_.x_ /2) + plane_coord_y_ * (y - rect_.size_.y_ /2) );
}



ColorF RayTracerWidget::trace_ray(const Ray& ray, short int depth) {
    Intersection min_obj = get_min_intersection_object(ray);
    if (min_obj.obj_ptr == nullptr) return AMBIENT;

    Vector3D normal = min_obj.obj_ptr->get_normal(ray, min_obj.distance);

    if (min_obj.obj_ptr->is_light_source_) {
        return min_obj.obj_ptr->material.actual_color_ * min_obj.obj_ptr->intensity;
    } else {
        if (depth >= depth_ - 1) {
            return AMBIENT;
        }
        Vector3D trace_point = ray.base_point_ + ray.direction_ * min_obj.distance + normal;

        
        RayIntersectableBasic* cur_env = get_cur_surrounding(trace_point);
        // RayIntersectableBasic* next_env = get_cur_surrounding(trace_point - 2 * normal);
        double cur_env_n = cur_env == nullptr ? 1.0 : cur_env->material.refract_n_;
        double sinAlpha2 = angleSin(-ray.direction_, normal) * cur_env_n / min_obj.obj_ptr->material.refract_n_;

        ColorF refraction_color = ColorF(0, 0, 0);

        if (min_obj.obj_ptr->material.is_transparent) {
            Ray refraction_ray(
                trace_point - 2*normal,
                (
                    (
                        sqrt(1 - sinAlpha2 * sinAlpha2) * 
                        (ray.direction_ - (normal * scalarMult(ray.direction_, normal) / ray.direction_.length())).normalize()
                    ) - normal * sinAlpha2
                ).normalize()
            );
            if (!(is_zero(refraction_ray.direction_.x_) && is_zero(refraction_ray.direction_.y_) && is_zero(refraction_ray.direction_.z_))) {
                refraction_color = trace_ray(refraction_ray, depth + 4);
                // refraction_color = trace_ray(refraction_ray, depth + 5);
                // printf("%lf cosalpha2\n", sqrt(1 - sinAlpha2 * sinAlpha2));
                // printf("pizdec");
            } else {
                // printf("ok------------------------\n");
            }
        }

        // ColorF refraction_color = ColorF(0, 0, 0);

        ColorF reflection_color = trace_ray(
            Ray(
                trace_point, 
                ray.direction_ + min_obj.obj_ptr->get_normal(ray, min_obj.distance)),
            depth + 1
        );

        

        //          LAMBERT
        short int lambert_it = 0;
        ColorF lambert_color = ColorF(0, 0, 0);
        // #pragma omp parallel for reduction(ColorPlus:reflection_color)
        for (lambert_it = 0; lambert_it < lambert_ray_cnt; ++lambert_it) {
            lambert_color += trace_lambert(ray, normal, min_obj.distance, depth + 1);
        }
        // https://t.me/folesis
        // https://t.me/eto0p


        //          DIFFUSE
        ColorF diffuse_color = ColorF(0, 0, 0);
        int light_source_cnt = 1;
        for (size_t it = 0; it < scene_items.size(); ++it) {
            if (scene_items[it]->is_light_source_) {
                light_source_cnt++;
                Ray light_source_ray(trace_point, scene_items[it]->get_direction(trace_point));
                Intersection light_source_intersection = get_min_intersection_object(light_source_ray);
                if (light_source_intersection.obj_ptr != scene_items[it]) continue;
                if (angleCos(normal, light_source_ray.direction_) < 0) continue;
                diffuse_color += light_source_intersection.obj_ptr->material.actual_color_ * angleCos(normal, light_source_ray.direction_);
            }
        }
        diffuse_color /= light_source_cnt;



        // return min_obj.obj_ptr->color_ * trace_ray(Ray(ray.base_point_ + ray.direction_ * min_obj.distance, ray.direction_ + min_obj.obj_ptr->get_normal(ray, min_obj.distance)), depth + 1);
        return  min_obj.obj_ptr->material.reflect_coeff_ * min_obj.obj_ptr->material.actual_color_ * reflection_color +
                min_obj.obj_ptr->material.actual_color_* diffuse_color + 
                min_obj.obj_ptr->material.lambert_coeff_ * lambert_color +
                refraction_color * min_obj.obj_ptr->material.refract_coeff_; 
            
    }
}

ColorF RayTracerWidget::trace_lambert(const Ray& ray, const Vector3D& normal, double distance, short int depth) {
    Vector3D ray_projection = ray.direction_ - normal * scalarMult(ray.direction_, normal);
    Vector3D ray_perpendicular = vectorMult(ray_projection, normal);
    return trace_ray
    (
        Ray(ray.base_point_ + ray.direction_ * distance + normal * 2, 
            normal + ray_projection * 2 * (double)(rand() - 15000) / RAND_MAX + ray_perpendicular * 2 * (double)(rand() - 15000) / RAND_MAX
        ),
        depth + lambert_depth_delta
    ) * lambert_coefficient;
    // rand() / RAND_MAX
}


// ColorF RayTracerWidget::calc_color()


Intersection RayTracerWidget::get_min_intersection_object(const Ray& ray) {
    Intersection min_obj = {nullptr, INFINITY};

    for (size_t it = 0; it < scene_items.size(); ++it) {
        double cur_distance = scene_items[it]->intersect(ray);
    
        if (cur_distance != NAN && cur_distance < min_obj.distance) {
            min_obj.obj_ptr = scene_items[it];
            min_obj.distance = cur_distance;
        }
    }

    return min_obj;
}

RayIntersectableBasic* RayTracerWidget::get_cur_surrounding(const Vector3D& point) {
    // double min_dist = INFINITY;
    // double refract_index = 1;

    for (size_t it = 0; it < scene_items.size(); ++it) {
        if(scene_items[it]->material.is_transparent) {
            if (scene_items[it]->is_inside(point)) {
                return scene_items[it];
            }
        }
    }

    return nullptr;
}

int RayTracerWidget::update_(Painter* painter) {
    if (hasChanged_) {
        repaint_(painter);
        return 1;
    }
    return 0;
}


int RayTracerWidget::repaint_(Painter* painter) {
    painter->begin(&this->self_surface_);
    size_t max_x = rect_.size_.x_;
    size_t max_y = rect_.size_.y_;
    size_t cur_y = 0;

    #pragma omp parallel for
    for (cur_y = 0; cur_y < max_y; ++cur_y) {
        size_t cur_x = 0;
        #pragma omp parallel for
        for (cur_x = 0; cur_x < max_x; ++cur_x) {
            ColorF color = trace_ray(calc_ray_direction(cur_x, cur_y), 0);
            color.a_ = 1.0;
            #pragma omp critical 
            {
                painter->setColor(color);
                painter->drawPoint(cur_x, cur_y);
            
                long bufpos = cur_y * 3 * max_x + ( 3 * max_x - 3 * cur_x );  
                scr_buff_[bufpos    ] = char(color.r_ * 255);
                scr_buff_[bufpos + 1] = char(color.g_ * 255);
                scr_buff_[bufpos + 2] = char(color.b_ * 255);
                // long newpos = ( max_y - cur_y - 1 ) * total_scanlinebytes + 3 * cur_x; 
                // scr_buff_[y]
            }
        }

        // printf("%d cur_y\n", cur_y);
        // #pragma omp critical
        // {
        //     painter->present();
        //     while(SDL_PollEvent(&event)) {};
        // }
    }
    painter->end();
    hasChanged_ = false;
    bmp_dump_tracer(scr_buff_, max_x, max_y);

    return 1;
}


// RayTracerWidget::
// RayTracerWidget::
// RayTracerWidget::
// RayTracerWidget::
