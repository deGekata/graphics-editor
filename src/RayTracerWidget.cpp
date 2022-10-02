#include "RayTracerWidget.hpp"





RayTracerWidget::RayTracerWidget
(
    double FOV, 
    const RectF& rect, 
    const PointF& point, 
    Widget* parent
):
    Widget(rect, point, parent)
{
    if (is_zero(FOV - M_PI)) throw;
    FOV_ = FOV;
    recalc_view_plane_dist();
    // rect_.p2_.x_ - rect.p1_.x_
    // screen_buffer = new ColorF[(rect_.p2_.x_ - rect.p1_.x_) * (rect_.p2_.y_ - rect.p1_.y_)];
}


RayTracerWidget::RayTracerWidget(
    const RectF& rect, 
    const PointF& point, 
    Widget* parent
): 
    Widget(rect, point, parent)
{
    FOV_ = M_PI / 2;
    recalc_view_plane_dist();
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
    view_plane_dist_ = tan(M_PI / 2 - FOV_ / 2) * (rect_.p2_.x_ - rect_.p1_.x_) / 2;
    if (is_zero(camera_direction_.x_) && is_zero(camera_direction_.y_)) 
        plane_coord_x_ = Vector3D(1, 0, 0);
    else
        plane_coord_x_ = Vector3D(-camera_direction_.x_, camera_direction_.y_, 0).normalize();
    plane_coord_y_ = vectorMult(camera_direction_, plane_coord_x_).normalize();
}

inline Ray RayTracerWidget::calc_ray_direction(int x, int y) {
    // Ray ret_val = Ray(
    //     camera_pos_, 
    //     camera_direction_ * view_plane_dist_ + plane_coord_x_ * (x - (rect_.p2_.x_ - rect_.p1_.x_) /2) + plane_coord_y_ * (y - (rect_.p2_.y_ - rect_.p1_.y_) /2) );
    // return ret_val;
    return Ray(
        camera_pos_, 
        camera_direction_ * view_plane_dist_ + plane_coord_x_ * (x - (rect_.p2_.x_ - rect_.p1_.x_) /2) + plane_coord_y_ * (y - (rect_.p2_.y_ - rect_.p1_.y_) /2) );
}



ColorF RayTracerWidget::trace_ray(const Ray& ray, short int depth) {
    Intersection min_obj = get_min_intersection_object(ray);
    if (min_obj.obj_ptr == nullptr) return AMBIENT;

    Vector3D normal = min_obj.obj_ptr->get_normal(ray, min_obj.distance);

    if (min_obj.obj_ptr->is_light_source_) {
        // return min_obj.obj_ptr->color_;
        return min_obj.obj_ptr->color_ * min_obj.obj_ptr->intensity;
    } else {
        if (depth >= depth_ - 1) {
            // printf("max_depth");
            // return ColorF(0, 0, 0);
            return AMBIENT;
        }

        ColorF ret_color = trace_ray(
            Ray(
                ray.base_point_ + ray.direction_ * min_obj.distance + normal, 
                ray.direction_ + min_obj.obj_ptr->get_normal(ray, min_obj.distance)),
            depth + 1
        );
        // #pragma omp for
        short int it = 0;
        ColorF lambert_color = ColorF(0, 0, 0);
        // #pragma omp parallel for reduction(ColorPlus:ret_color)
        for (it = 0; it < lambert_ray_cnt; ++it) {
            lambert_color += trace_lambert(ray, normal, min_obj.distance, depth + 1);
        }
        // return min_obj.obj_ptr->color_ * trace_ray(Ray(ray.base_point_ + ray.direction_ * min_obj.distance, ray.direction_ + min_obj.obj_ptr->get_normal(ray, min_obj.distance)), depth + 1);
        return min_obj.obj_ptr->color_ * ret_color + lambert_color * min_obj.obj_ptr->color_;
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


int RayTracerWidget::paint(Painter* painter) {
    size_t max_x = rect_.p2_.x_ - rect_.p1_.x_;
    size_t max_y = rect_.p2_.y_ - rect_.p1_.y_;
    size_t cur_y = 0;
    #pragma omp parallel for
    for (cur_y = 0; cur_y < max_y; ++cur_y) {
        size_t cur_x = 0;
        #pragma omp parallel for
        for (cur_x = 0; cur_x < max_x; ++cur_x) {
            ColorF color = trace_ray(calc_ray_direction(cur_x, cur_y), 0);
            #pragma omp critical 
            {
                painter->setColor(color);
                painter->drawPoint(cur_x, cur_y);
            }
        }
        // printf("%d cur_y\n", cur_y);
        #pragma omp critical
        {
            painter->present();
        }
    }

    return 0;
}


// RayTracerWidget::
// RayTracerWidget::
// RayTracerWidget::
// RayTracerWidget::





